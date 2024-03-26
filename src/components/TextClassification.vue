<template>
    <div>
        <el-card class="teachcard">
            <div slot="header" style="display: flex;justify-content: left;align-items: center;">
                <el-page-header @back="goBack" :content="project.name">
                </el-page-header>
                <span>{{ project.projectName }}->{{ project.version }}->{{ project.callType }}</span>
            </div>
            <div style="border: 1px solid #eee;height: 585px;display: flex;">
                <el-card class="teachcard" style="width: 1050px;">
                    <div slot="header" class="operation">
                        <div class="button-wrap">
                            <i @click="save(nowselect - 1)" class="el-icon-back"
                                style="cursor: pointer;font-size: 20px;"></i>
                            <el-tooltip content="保存" placement="top-end">
                                <div class="toolblock">
                                    <el-button @click="save(nowselect)" type="text"
                                        class="el-icon-suitcase button"></el-button>
                                </div>
                            </el-tooltip>
                        </div>
                        <i @click="save(nowselect + 1)" class="el-icon-right"
                            style="cursor: pointer;font-size: 20px;"></i>
                    </div>
                    <div style="display: flex;justify-content: space-around;align-items: flex-start;">
                        <div
                            style="display: flex;flex-direction: column;justify-content: space-between;align-items: center;">
                            <div v-if="textdata.length > 0" style="width: 830px;height: 480px;">{{
                    textdata[nowselect].text }}</div>
                        </div>
                        <div class="mapresult">
                            <div class="mapresultheader">标注结果</div>
                            <div v-if="textdata.length > 0">
                                <div>{{ textdata[nowselect].result }}</div>
                            </div>
                            <div v-else>
                                <el-empty description="请在右侧选择标签"></el-empty>
                            </div>
                        </div>
                    </div>
                </el-card>
                <div class="mapresult2">
                    <div>
                        <div style="color: #666;font-size: 20px;padding: 5px;font-weight: 600;width: 195px;">
                            <span>分类标签</span>
                        </div>
                    </div>
                    <div
                        style="height: 400px;overflow-x:auto;overflow-y: auto;margin-left: 15px;display: flex;flex-direction: column;justify-content: flex-start;align-items: center;">
                        <div @click="choose(item)" v-for="item in label" :key="item.label" class="labelblock">
                            <div :style="'backgroundColor:' + item.color" style="width: 25px;height: 25px;"></div>
                            <span style="margin-left: 15px;">{{ item.label }}</span>
                        </div>
                    </div>
                </div>
            </div>
        </el-card>
    </div>
</template>

<script>
import axios from 'axios'
export default {
    name: "TextClassification",
    components: {

    },
    data() {
        return {
            project: {},
            gMap: null,
            mode: "",
            chooselabel: [],
            search: "",
            label: [],
            addlabelvisible: false,
            emptylabel: false,
            labelerror: "",
            labelsure: "待添加",
            labelvalue: "",
            nowselect: 0,
            page: 1,
            textdata: []
        }
    },
    computed: {

    },
    methods: {
        save(index) {
            let jsondata = JSON.stringify([this.textdata[this.nowselect]])
            let file = new FormData()
            const blob = new Blob([jsondata]);
            file.set("file", blob, "data.json")
            file.set("id", this.textdata[this.nowselect].id)
            axios.put("http://120.26.142.114:10010/dataset/call", file, { headers: { "Content-Type": "multipart/form-data;charset=utf-8" } }).then((res) => {
                console.log(res.data);
                if (res.data.code == 200) {
                    this.$message.success("保存成功")
                } else {
                    this.$message.error("保存失败")
                }
            })
            if (this.page === 1 && index === -1) {
                this.$message.warning("已经是第一张了")
                return
            } else if (index === this.textdata.length || index == -1) {
                this.page = index == -1 ? this.page - 1 : this.page + 1
                this.getdata(this.page, index == -1 ? 0 : 1)
            } else {
                this.nowselect = index
            }
        },
        choose(item) {
            this.textdata[this.nowselect].result = item.label
        },
        goBack() {
            this.$router.push("/MakeMark")
        },
        pop(index) {
            console.log(index);
            this.chooselabel.splice(index, 1)
        },
        getdata(page, num) {
            axios.post("http://120.26.142.114:10010" + (this.project.identity == 0 ? '/dataset/task' : '/dataset/admin/select'), { version: this.project.versionId, page: page, number: 5, current: page, pageSize: 5 })
                .then(res => {
                    console.log(res.data);
                    this.textdata.splice(0)
                    if (this.project.identity == 0) {
                        res.data.data.forEach(item => {
                            if (item.mark) {
                                axios.get(item.mark)
                                    .then(res2 => {
                                        this.textdata = this.textdata.concat(res2.data)
                                    })
                                    .catch(e2 => {
                                        console.log(e2);
                                    })
                            } else {
                                axios.get(item.url)
                                    .then(res2 => {
                                        this.textdata = this.textdata.concat([{ id: item.id, text: res2.data, result: "" }])
                                    })
                                    .catch(e2 => {
                                        console.log(e2);
                                    })
                            }
                        })
                    } else if (this.project.identity == 1) {
                        res.data.data.datasetCallNewVOS.forEach(item => {
                            if (item.calloutPath) {
                                axios.get(item.calloutPath)
                                    .then(res2 => {
                                        this.textdata = this.textdata.concat(res2.data)
                                    })
                                    .catch(e2 => {
                                        console.log(e2);
                                    })
                            } else {
                                axios.get(item.ossPath)
                                    .then(res2 => {
                                        this.textdata = this.textdata.concat([{ id: item.id, text: res2.data, result: "" }])
                                    })
                                    .catch(e2 => {
                                        console.log(e2);
                                    })
                            }
                        })
                    }

                    this.nowselect = num == 1 ? 0 : 4
                })
                .catch(e => {
                    console.log(e);
                })
        },
        getlabel() {
            axios.get("http://120.26.142.114:10010/task/label/" + this.project.versionId)
                .then(res => {
                    this.label = res.data.data
                })
                .catch(e => {
                    console.log(e);
                })
        }
    },
    mounted() {
        console.log(this.$route.query);
        this.project = this.$route.query
        this.getdata(this.page, 1)
        this.getlabel()
    },
}
</script>

<style scoped>
.operation {
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.teachcard {
    text-align: left;
    margin-top: 5px;
}

/deep/.el-card__header {
    padding: 15px;
}

/deep/.el-card__body {
    padding: 5px;
}

.button-wrap {
    display: flex;
    padding-bottom: 5px;
    justify-content: left;
    position: relative;
    z-index: 99;
}

#map {
    /* margin: 0 auto; */
    overflow: hidden;
    position: relative;
    height: 360px;
    width: 480px;
    margin-top: 5px;
    margin-left: 25px;
    border: 1px dashed #ccc;
}

.mapresult {
    border: 1px solid #eee;
    height: 485px;
    width: 220px;
    margin-top: 6px;
    overflow-y: auto;
}

.mapresult2 {
    border: 1px solid #eee;
    height: 562px;
    width: 280px;
    margin-top: 6px;
    margin-left: 15px;
}

.mapresultheader {
    font-size: 16px;
    font-weight: 600;
    word-break: break-all;
    color: #666;
    padding: 30px 20px;
    border-bottom: 1px solid #eee;
}

.mapresultheader2 {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 10px 10px;
    border-bottom: 1px solid #eee;
    line-height: 32px;
    height: 30px;
    z-index: 1;
}

.button {
    font-size: 20px;
    color: rgb(100, 100, 101);
    cursor: pointer;
}

.button:hover {
    color: rgb(36, 104, 242);
}

.toolblock {
    width: 30px;
    margin-left: 8px;
    height: 30px;
    display: flex;
    align-items: center;
    justify-content: center;
}

.toolblock:hover {
    background-color: rgb(209, 227, 250);
    color: rgb(36, 104, 242);
}

.modeing {
    background-color: rgb(209, 227, 250);
}

.select {
    border: 3px solid rgb(36, 104, 242);
    border-radius: 3px;
}

.toparrow {
    cursor: pointer;
    font-size: 25px;
}

.toparrow:hover {
    color: rgb(36, 104, 240);
}

/deep/.el-divider--horizontal {
    display: block;
    height: 0.5px;
    width: 100%;
    margin: 0px 0px;
}

.result {
    border: 2px solid rgb(36, 104, 240);
    border-radius: 5px;
    display: flex;
    flex-direction: column;
    justify-content: flex-start;
    align-items: flex-start;
    width: 150px;
    margin-top: 10px;
    cursor: pointer;
    background-color: rgb(209, 227, 250);
    padding: 8px;
}

.resultheader {
    padding: 10px;
}

.labelblock {
    border: 1px solid rgb(221, 221, 221);
    display: flex;
    justify-content: space-between;
    align-items: center;
    height: 35px;
    width: 160px;
    padding-left: 5px;
    cursor: pointer;
}

.labelblock:hover {
    border: 1px solid rgb(36, 104, 242);
}

.tip {
    font-size: 12px;
    text-align: center;
    color: #999;
    line-height: 17px;
    margin-top: 10px;
}

.label {
    display: flex;
    justify-content: left;
    align-items: center;
    margin-top: 8px;
    border: 1px solid #eee;
    padding: 8px;
    width: 215px;
}

.label:hover {
    border: 1px solid rgb(36, 104, 242);
}

.choose {
    border: 1px solid rgb(36, 104, 242);
}

.input {
    width: 70%;
    height: 25px;
    padding: 0;
    font-size: 12px;
}

.labelicon {
    margin-left: 12px;
    cursor: pointer;
}

.labelicon:hover {
    color: rgb(36, 104, 242);
}

@keyframes shake {
    0% {
        transform: translate(0, 0);
    }

    10% {
        transform: translate(-5px, -5px);
    }

    20% {
        transform: translate(5px, 5px);
    }

    30% {
        transform: translate(-5px, -5px);
    }

    40% {
        transform: translate(5px, 5px);
    }

    50% {
        transform: translate(-5px, -5px);
    }

    60% {
        transform: translate(5px, 5px);
    }

    70% {
        transform: translate(-5px, -5px);
    }

    80% {
        transform: translate(5px, 5px);
    }

    90% {
        transform: translate(-5px, -5px);
    }

    100% {
        transform: translate(0, 0);
    }
}

#repeattext {
    animation: shake 0.8s 1 forwards;
    color: red;
    font-size: 12px;
    text-align: left;
}

.suretext {
    color: rgb(192, 196, 204);
    font-size: 12px;
    text-align: left;
}

.addok {
    color: green;
}

.selected {
    border: 2px solid rgb(36, 104, 242);
}

.labelblock {
    border: 1px solid rgb(221, 221, 221);
    display: flex;
    justify-content: flex-start;
    align-items: center;
    height: 65px;
    width: 190px;
    padding-left: 5px;
    cursor: pointer;
    margin-bottom: 15px;
}

.labelblock:hover {
    border: 1px solid rgb(36, 104, 242);
}

.button-wrap {
    display: flex;
    padding-bottom: 5px;
    justify-content: left;
    align-items: center;
    position: relative;
    z-index: 99;
}

.operation {
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.notify {
    height: 10%;
}
</style>