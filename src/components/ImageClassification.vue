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
                            <el-tooltip content="缩小" placement="top-end">
                                <div class="toolblock">
                                    <el-button type="text" class="el-icon-zoom-out button" @click="zoomOut"></el-button>
                                </div>
                            </el-tooltip>
                            <el-tooltip content="放大" placement="top-end">
                                <div class="toolblock">
                                    <el-button type="text" class="el-icon-zoom-in button" @click="zoomIn"></el-button>
                                </div>
                            </el-tooltip>
                            <el-tooltip content="平移" placement="top-start">
                                <div class="toolblock" :class="{ modeing: mode === 'PAN' }">
                                    <el-button type="text" class="el-icon-thumb button"></el-button>
                                </div>
                            </el-tooltip>
                            <el-tooltip content="保存" placement="top-end">
                                <div class="toolblock">
                                    <el-button @click="save((page - 1) * 5 + nowselect)" type="text"
                                        class="el-icon-suitcase button"></el-button>
                                </div>
                            </el-tooltip>
                        </div>
                        <div style="display: flex;align-items: center;margin-right: 8px;">
                            <i @click="save(nowselect - 1)" style="cursor: pointer;font-size: 12px;"
                                class="el-icon-arrow-left toparrow"></i>
                            <span style="font-size: 12px;">第{{ nowselect + 1 }}张/一共4张</span>
                            <i @click="save(nowselect + 1)" style="cursor: pointer;font-size: 12px;"
                                class="el-icon-arrow-right toparrow"></i>
                        </div>
                    </div>
                    <div style="display: flex;justify-content: space-around;align-items: flex-start;">
                        <div
                            style="display: flex;flex-direction: column;justify-content: space-between;align-items: center;">
                            <div id="map"></div>
                            <div style="display: flex;justify-content: center;align-items: center;">
                                <i @click="save(nowselect - 1)" class="el-icon-arrow-left button"></i>
                                <img @click="save((page - 1) * 5 + index)"
                                    style="cursor: pointer;width: 100px;height: 100px;margin-left: 15px;"
                                    :class="{ selected: (nowselect) % 5 === index }" :src="item.url"
                                    v-for="(item, index) in imagelist.slice((page - 1) * 5, page * 5)" :key="item.url">
                                <i @click="save(nowselect + 1)" class="el-icon-arrow-right button"></i>
                            </div>
                        </div>
                        <div class="mapresult">
                            <div class="mapresultheader">标注结果</div>
                            <div v-if="chooselabel.length > 0">
                                <div v-for="(item, index) in chooselabel" :key="index"
                                    style="display: flex;justify-content: left;align-items: center;margin-top: 8px;margin-left: 8px;">
                                    <div style="margin-left: 15px;display: flex;justify-content: left;align-items: center;">
                                        <div class="labelblock" :id="`labeldiv${index + 1}`">
                                            <span>{{ item }}</span>
                                            <i class="el-icon-error" style="margin-right: 5px;" @click="pop(index)"></i>
                                        </div>
                                    </div>
                                </div>
                            </div>
                            <div v-else>
                                <el-empty description="请在右侧选择标签"></el-empty>
                            </div>
                        </div>
                    </div>
                </el-card>
                <div class="mapresult2">
                    <div>
                        <div v-if="!addlabelvisible" class="mapresultheader2">
                            <span
                                style="font-size: 16px;color: #000;letter-spacing: 0;text-align: left;line-height: 22px;flex: 1;">
                                标签栏
                            </span>
                            <el-button style="background-color: rgb(36,104,242);font-size: 12px;color: white;" size="mini"
                                @click="addlabelvisible = true">
                                <i class="el-icon-price-tag"></i>
                                添加标签
                            </el-button>
                        </div>
                        <div v-else
                            style="display: flex;flex-direction: column;align-items: left;justify-content:flex-start;padding: 10px 10px;border-bottom: 1px solid #eee;line-height: 32px;">
                            <div style="display: flex;justify-content: left;align-items: center;">
                                <input class="input" size="mini" v-model="labelvalue" placeholder="请输入标签名称，不支持重复标签">
                                <el-tooltip content="确认添加标签" placement="top-start">
                                    <i class="el-icon-check labelicon" @click="surelabelinput"></i>
                                </el-tooltip>
                                <el-tooltip content="取消添加" placement="top-start">
                                    <i class="el-icon-close labelicon" @click="closelabelinput"></i>
                                </el-tooltip>
                            </div>
                            <span v-if="emptylabel" id="repeattext" class="animate__animated animate__shakeX">
                                {{ labelerror }}
                            </span>
                            <span v-else class="suretext" :class="{ addok: labelsure !== '待添加' }">
                                {{ labelsure }}
                            </span>
                        </div>
                    </div>
                    <div style="padding: 15px;border-bottom: 1px solid #eee;text-align: center;">
                        <el-input suffix-icon="el-icon-search" v-model="search" placeholder="请输入标签名称"
                            size="medium"></el-input>
                        <div class="tip">根据图片内容，选择标签<br>标注员临时定义的标签无法保存</div>
                    </div>
                    <el-checkbox-group v-model="chooselabel" style="overflow-y: auto;height: 380px;">
                        <el-checkbox v-for="(item, index) in showlabel" :key="index" class="label"
                            :class="{ choose: chooselabel.includes(item) }" :label="item">
                            {{ item }}
                        </el-checkbox>
                    </el-checkbox-group>
                </div>
            </div>
        </el-card>
    </div>
</template>
<script>
import axios from 'axios'
import AILabel from "ailabel";
export default {
    name: "ImageClassification",
    components: {

    },
    data() {
        return {
            project: { projectid: "fdsafd", projectname: "dsa", version: "v1", marktype: "信息抽取标注" },
            gMap: null,
            mode: "",
            chooselabel: [],
            search: "",
            label: ["狗", "猫", "鸟类", "鱼类", "汽车", "自行车", "飞机", "船", "成年人", "儿童", "老年人", "山脉", "森林", "河流", "食物", "水果", "蔬菜", "主食", "饮料", "建筑", "城市建筑", "农村房屋", "古老建筑"],
            addlabelvisible: false,
            emptylabel: false,
            labelerror: "",
            labelsure: "待添加",
            labelvalue: "",
            imagelist: [
                {
                    url: "http://120.55.63.197:3000/images/甘达.webp.jpg",
                    label: [],
                    access: false
                },
                {
                    url: "http://120.55.63.197:3000/images/卡拉什.webp.jpg",
                    label: [],
                    access: false
                },
                {
                    url: "http://120.55.63.197:3000/images/熔岩.webp.jpg",
                    label: [],
                    access: false
                },
                {
                    url: "http://120.55.63.197:3000/images/竹木.webp.jpg",
                    label: [],
                    access: false
                },
            ],
            imagelist2: [
                {
                    url: "/图像标注/15.webp (1).jpg",
                    label: [""],
                    access: false
                },
                {
                    url: "/图像标注/17.jpg",
                    label: ["金融"],
                    access: false
                },
                {
                    url: "/图像标注/18.jpg",
                    label: ["财务报表"],
                    access: false
                },
                {
                    url: "/图像标注/19.jpg",
                    label: ["金融"],
                    access: false
                },
                {
                    url: "/图像标注/2.webp.jpg",
                    label: ["金融"],
                    access: false
                },
            ],
            nowselect: 0,
            page: 1
        }
    },
    computed: {
        showlabel() {
            return this.label.filter(item => {
                return item.includes(this.search) || this.search === ""
            })
        }
    },
    methods: {
        save(index) {
            this.imagelist[this.nowselect].label = this.chooselabel
            if (index === -1) {
                this.imagelist[index + 1].label = this.chooselabel
                this.$message.warning("已经是第一张图片了")
                return
            } else if (index === this.imagelist.length) {
                if (index === 10) {
                    this.$message.warning("已经是最后一张图片了")
                    return
                } else {
                    this.imagelist2.map(item => {
                        this.imagelist.push(item)
                    })
                }
            }
            this.gMap.destroy()
            this.createLayer(this.imagelist[index])
            this.nowselect = index
            this.page = Math.floor(this.nowselect / 5 + 1)
        },
        closelabelinput() {
            this.labelvalue = ""
            this.emptylabel = false
            this.addlabelvisible = false
            this.labelsure = "待添加"
        },
        surelabelinput() {
            if (this.labelvalue && !this.label.includes(this.labelvalue)) {
                this.label.push(this.labelvalue)
                this.labelvalue = ""
                this.labelsure = "添加成功"
                this.emptylabel = false
                return
            } else if (this.labelvalue === "") {
                this.labelerror = "标签名称不能为空"
                this.emptylabel = true
            } else {
                this.labelerror = "标签名称重复"
                this.emptylabel = true
            }
        },
        goBack() {
            this.$router.push("/MakeMark")
        },
        pop(index) {
            console.log(index);
            this.chooselabel.splice(index, 1)
        },
        createLayer(item) {
            const gMap = new AILabel.Map("map", {
                center: { x: 250, y: 187 },  // 确定中心点
                zoom: 500,
                mode: "PAN", // 绘制线段
                //refreshDelayWhenZooming: false, // 缩放时是否允许刷新延时，性能更优
                zoomWhenDrawing: true,
                panWhenDrawing: true,
                // 控制滑轮缩放缩率[0, 10), 值越小，则缩放越快，反之越慢
                withHotKeys: false, // 关闭快捷键,
                autoFeatureSelect: true,
                //drawZoom: false,
                //autoPan: false,
            });
            this.gMap = gMap;
            this.chooselabel = item.label
            const gFirstImageLayer = new AILabel.Layer.Image(
                "first-layer-image", // id
                {
                    id: "image",
                    src: item.url,
                    width: 500,
                    height: 375,
                    crossOrigin: true, // 如果跨域图片，需要设置为true
                    position: {
                        // 左上角相对中心点偏移量
                        x: 0,
                        y: 0,
                    },
                    // 网格
                    grid: false
                }, // imageInfo
                { name: "第一个图片图层" }, // props
                { zIndex: 5 } // style
            );
            // 添加到gMap对象
            gMap.addLayer(gFirstImageLayer);
            if (item.label.length === 0) {
                axios.post("http://home.itzyc.com:12349/img/", { url: item.url },{timeout:500000000000}).then(res => {
                    console.log(res.data);
                    this.chooselabel.push(res.data.label)
                })
            }
            //this.chooselabel = item.label
        },
        zoomIn() {
            this.gMap.zoomIn();
        },
        zoomOut() {
            this.gMap.zoomOut();
        },
    },
    mounted() {
        this.project = this.$route.query
        /*请求图片*/
        this.createLayer(this.imagelist[0])
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
</style>