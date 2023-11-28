<template>
    <div style="padding: 15px;margin-top: 15px;">
        <el-card>
            <div slot="header">
                <el-menu :default-active="'1'" mode="horizontal" @select="select">
                    <el-menu-item index="1" @click="mode = 1">信息抽取标注</el-menu-item>
                    <el-menu-item index="2" @click="mode = 2">图像文本标注</el-menu-item>
                    <el-menu-item index="3" @click="mode = 3">文本分类标注</el-menu-item>
                    <el-menu-item index="4" @click="mode = 4">图片分类标注</el-menu-item>
                </el-menu>
            </div>
            <div v-if="mode === 1">
                <div style="height: 500px;display: flex;justify-content: space-around;">
                    <div style="height: 100%;width: 50%;text-align: left;">
                        <span style="font-weight:600;color:rgb(100,100,101);font-size:20px;margin-left: 38px;">标注规范</span>
                        <el-form :model="standard" ref="form1" label-width="150px" class="form" label-position="left">
                            <el-form-item class="formitem" label="最大数据数量">
                                <div style="display: flex;align-items: center;">
                                    <el-input :disabled="!emailedit" v-model="standard.maxnumber" size="mini"
                                        style="width: 40%;"></el-input>
                                    <el-button type="primary" size="mini"
                                        style="height: 15%;width: 13%;margin-left: 15px;"><i class="el-icon-edit"
                                            style="font-size: 16px;" @click="emailedit = !emailedit"></i></el-button>
                                </div>
                            </el-form-item>
                            <el-form-item label="文件大小" class="formitem">
                                <el-input :disabled="!sizeedit" v-model="standard.maxsize" size="mini"
                                    style="width: 40%;"></el-input>
                                <el-button type="primary" size="mini" style="height: 15%;width: 13%;margin-left: 15px;"><i
                                        class="el-icon-edit" style="font-size: 16px;"
                                        @click="sizeedit = !sizeedit"></i></el-button>
                            </el-form-item>
                            <el-form-item label="发布合格率" class="formitem">
                                <el-input :disabled="!sizeedit" v-model="standard.publish" size="mini"
                                    style="width: 40%;"></el-input>
                                <el-button type="primary" size="mini" style="height: 15%;width: 13%;margin-left: 15px;"><i
                                        class="el-icon-edit" style="font-size: 16px;"
                                        @click="publishedit = !publishedit"></i></el-button>
                            </el-form-item>
                            <el-form-item label="最大团队成员个数" class="formitem">
                                <el-input :disabled="!sizeedit" v-model="standard.parter" size="mini"
                                    style="width: 40%;"></el-input>
                                <el-button type="primary" size="mini" style="height: 15%;width: 13%;margin-left: 15px;"><i
                                        class="el-icon-edit" style="font-size: 16px;"
                                        @click="partedit = !partedit"></i></el-button>
                            </el-form-item>
                            <el-form-item label="标注范例" class="formitem">
                                <el-upload action="" :show-file-list="false" class="tableplay" :auto-upload="false"
                                    :on-change="handlechange">上传示例图片</el-upload>
                            </el-form-item>
                        </el-form>
                        <el-divider></el-divider>
                    </div>
                    <div style="display: flex;justify-content: space-around">
                        <img :src="choose" width="600" height="500">
                        <div style="display: block;overflow-y: scroll;width: 180px;">
                            <img class="pic" :class="{ chose: item === choose }" v-for="item in example[mode - 1]"
                                :key="item" :src="item" width="150" height="150" @click="choose = item">
                        </div>
                    </div>
                </div>
            </div>
            <div v-if="mode === 2">
                <div style="height: 500px;display: flex;justify-content: space-around;">
                    <div style="height: 100%;width: 50%;text-align: left;">
                        <span style="font-weight:600;color:rgb(100,100,101);font-size:20px;margin-left: 38px;">标注规范</span>
                        <el-form :model="standard" ref="form1" label-width="150px" class="form" label-position="left">
                            <el-form-item class="formitem" label="最大数据数量">
                                <div style="display: flex;align-items: center;">
                                    <el-input :disabled="!emailedit" v-model="standard.maxnumber" size="mini"
                                        style="width: 40%;"></el-input>
                                    <el-button type="primary" size="mini"
                                        style="height: 15%;width: 13%;margin-left: 15px;"><i class="el-icon-edit"
                                            style="font-size: 16px;" @click="emailedit = !emailedit"></i></el-button>
                                </div>
                            </el-form-item>
                            <el-form-item label="文件大小" class="formitem">
                                <el-input :disabled="!sizeedit" v-model="standard.maxsize" size="mini"
                                    style="width: 40%;"></el-input>
                                <el-button type="primary" size="mini" style="height: 15%;width: 13%;margin-left: 15px;"><i
                                        class="el-icon-edit" style="font-size: 16px;"
                                        @click="sizeedit = !sizeedit"></i></el-button>
                            </el-form-item>
                            <el-form-item label="发布合格率" class="formitem">
                                <el-input :disabled="!sizeedit" v-model="standard.publish" size="mini"
                                    style="width: 40%;"></el-input>
                                <el-button type="primary" size="mini" style="height: 15%;width: 13%;margin-left: 15px;"><i
                                        class="el-icon-edit" style="font-size: 16px;"
                                        @click="publishedit = !publishedit"></i></el-button>
                            </el-form-item>
                            <el-form-item label="最大团队成员个数" class="formitem">
                                <el-input :disabled="!sizeedit" v-model="standard.parter" size="mini"
                                    style="width: 40%;"></el-input>
                                <el-button type="primary" size="mini" style="height: 15%;width: 13%;margin-left: 15px;"><i
                                        class="el-icon-edit" style="font-size: 16px;"
                                        @click="partedit = !partedit"></i></el-button>
                            </el-form-item>
                            <el-form-item label="标注范例" class="formitem">
                                <el-upload action="" :show-file-list="false" class="tableplay" :auto-upload="false"
                                    :on-change="handlechange">上传示例图片</el-upload>
                            </el-form-item>
                        </el-form>
                        <el-divider></el-divider>
                    </div>
                    <div style="display: flex;justify-content: space-around">
                        <img :src="choose" width="600" height="500">
                        <div style="display: block;overflow-y: scroll;width: 180px;">
                            <img class="pic" :class="{ chose: item === choose }" v-for="item in example[mode - 1]"
                                :key="item" :src="item" width="150" height="150" @click="choose = item">
                        </div>
                    </div>
                </div>
            </div>
            <div v-if="mode === 3">
                <div style="height: 500px;display: flex;justify-content: space-around;">
                    <div style="height: 100%;width: 50%;text-align: left;">
                        <span style="font-weight:600;color:rgb(100,100,101);font-size:20px;margin-left: 38px;">标注规范</span>
                        <el-form :model="standard" ref="form1" label-width="150px" class="form" label-position="left">
                            <el-form-item class="formitem" label="最大数据数量">
                                <div style="display: flex;align-items: center;">
                                    <el-input :disabled="!emailedit" v-model="standard.maxnumber" size="mini"
                                        style="width: 40%;"></el-input>
                                    <el-button type="primary" size="mini"
                                        style="height: 15%;width: 13%;margin-left: 15px;"><i class="el-icon-edit"
                                            style="font-size: 16px;" @click="emailedit = !emailedit"></i></el-button>
                                </div>
                            </el-form-item>
                            <el-form-item label="文件大小" class="formitem">
                                <el-input :disabled="!sizeedit" v-model="standard.maxsize" size="mini"
                                    style="width: 40%;"></el-input>
                                <el-button type="primary" size="mini" style="height: 15%;width: 13%;margin-left: 15px;"><i
                                        class="el-icon-edit" style="font-size: 16px;"
                                        @click="sizeedit = !sizeedit"></i></el-button>
                            </el-form-item>
                            <el-form-item label="发布合格率" class="formitem">
                                <el-input :disabled="!sizeedit" v-model="standard.publish" size="mini"
                                    style="width: 40%;"></el-input>
                                <el-button type="primary" size="mini" style="height: 15%;width: 13%;margin-left: 15px;"><i
                                        class="el-icon-edit" style="font-size: 16px;"
                                        @click="publishedit = !publishedit"></i></el-button>
                            </el-form-item>
                            <el-form-item label="最大团队成员个数" class="formitem">
                                <el-input :disabled="!sizeedit" v-model="standard.parter" size="mini"
                                    style="width: 40%;"></el-input>
                                <el-button type="primary" size="mini" style="height: 15%;width: 13%;margin-left: 15px;"><i
                                        class="el-icon-edit" style="font-size: 16px;"
                                        @click="partedit = !partedit"></i></el-button>
                            </el-form-item>
                            <el-form-item label="标注范例" class="formitem">
                                <el-upload action="" :show-file-list="false" class="tableplay" :auto-upload="false"
                                    :on-change="handlechange">上传示例图片</el-upload>
                            </el-form-item>
                        </el-form>
                        <el-divider></el-divider>
                    </div>
                    <div style="display: flex;justify-content: space-around">
                        <img :src="choose" width="600" height="500">
                        <div style="display: block;overflow-y: scroll;width: 180px;">
                            <img class="pic" :class="{ chose: item === choose }" v-for="item in example[mode - 1]"
                                :key="item" :src="item" width="150" height="150" @click="choose = item">
                        </div>
                    </div>
                </div>
            </div>
            <div v-if="mode === 4">
                <div style="height: 500px;display: flex;justify-content: space-around;">
                    <div style="height: 100%;width: 50%;text-align: left;">
                        <span style="font-weight:600;color:rgb(100,100,101);font-size:20px;margin-left: 38px;">标注规范</span>
                        <el-form :model="standard" ref="form1" label-width="150px" class="form" label-position="left">
                            <el-form-item class="formitem" label="最大数据数量">
                                <div style="display: flex;align-items: center;">
                                    <el-input :disabled="!emailedit" v-model="standard.maxnumber" size="mini"
                                        style="width: 40%;"></el-input>
                                    <el-button type="primary" size="mini"
                                        style="height: 15%;width: 13%;margin-left: 15px;"><i class="el-icon-edit"
                                            style="font-size: 16px;" @click="emailedit = !emailedit"></i></el-button>
                                </div>
                            </el-form-item>
                            <el-form-item label="文件大小" class="formitem">
                                <el-input :disabled="!sizeedit" v-model="standard.maxsize" size="mini"
                                    style="width: 40%;"></el-input>
                                <el-button type="primary" size="mini" style="height: 15%;width: 13%;margin-left: 15px;"><i
                                        class="el-icon-edit" style="font-size: 16px;"
                                        @click="sizeedit = !sizeedit"></i></el-button>
                            </el-form-item>
                            <el-form-item label="发布合格率" class="formitem">
                                <el-input :disabled="!sizeedit" v-model="standard.publish" size="mini"
                                    style="width: 40%;"></el-input>
                                <el-button type="primary" size="mini" style="height: 15%;width: 13%;margin-left: 15px;"><i
                                        class="el-icon-edit" style="font-size: 16px;"
                                        @click="publishedit = !publishedit"></i></el-button>
                            </el-form-item>
                            <el-form-item label="最大团队成员个数" class="formitem">
                                <el-input :disabled="!sizeedit" v-model="standard.parter" size="mini"
                                    style="width: 40%;"></el-input>
                                <el-button type="primary" size="mini" style="height: 15%;width: 13%;margin-left: 15px;"><i
                                        class="el-icon-edit" style="font-size: 16px;"
                                        @click="partedit = !partedit"></i></el-button>
                            </el-form-item>
                            <el-form-item label="标注范例" class="formitem">
                                <el-upload action="" :show-file-list="false" class="tableplay" :auto-upload="false"
                                    :on-change="handlechange">上传示例图片</el-upload>
                            </el-form-item>
                        </el-form>
                        <el-divider></el-divider>
                    </div>
                    <div style="display: flex;justify-content: space-around">
                        <img :src="choose" width="600" height="500">
                        <div style="display: block;overflow-y: scroll;width: 180px;">
                            <img class="pic" :class="{ chose: item === choose }" v-for="item in example[mode - 1]"
                                :key="item" :src="item" width="150" height="150" @click="choose = item">
                        </div>
                    </div>
                </div>
            </div>
        </el-card>

    </div>
</template>
<script>
export default {
    name: "PlatformRegulation",
    components: {

    },
    data() {
        return {
            publishedit: false,
            partedit: false,
            sizeedit: false,
            emailedit: false,
            mode: 1,
            standard: {
                maxnumber: 5000,
                maxsize: 20,
                publish: 95,
                parter: 20
            },
            example: [
                ["/example1.jpg", "/example2.jpg", "/example3.jpg"],
                ["/example4.jpg", "/example5.jpg", "/example6.jpg"],
                ["/example1.jpg", "/example2.jpg", "/example3.jpg"],
                ["/example4.jpg", "/example5.jpg", "/example6.jpg"]
            ],
            choose: ""
        }
    },
    computed: {

    },
    methods: {
        handlechange(file) {
            const fs = new FileReader()
            fs.readAsDataURL(file.raw)
            fs.onload = (e) => {
                //console.log(e.target.result);
                this.choose = e.target.result
                this.example[this.mode - 1].push(e.target.result)
            }
        },
        handleClick(tab, event) {
            console.log(tab, event);
        },
        select(index) {
            this.choose = this.example[parseInt(index) - 1][0]
        }
    },
    mounted() {
        this.choose = this.example[this.mode - 1][0]
    },
}
</script>
<style scoped>
.teachcard {
    text-align: left;
    margin: 10px;
}

/deep/.el-card__header {
    padding: 8px;
    padding-bottom: 0px;
}

.el-menu-item {
    padding: 0px;
    margin-left: 30px;
    font-size: 16px;
}

.el-menu--horizontal>.el-menu-item.is-active {
    border-bottom: 2px solid #409EFF;
    color: rgb(36, 104, 242);
}

.boxCard1 {
    width: 100%;
    margin-left: 1%;
    height: 590px;
    background-color: #fff;
}

.boxCard2 {
    width: 100%;
    margin-left: 1%;
    height: 590px;
    background-color: rgb(36, 46, 62);
}

.cardheader {
    display: flex;
    justify-content: left;
    padding-left: 15px;
    align-items: center;
    font-size: 25px;
}

.cardheader2 {
    display: flex;
    justify-content: left;
    padding-left: 15px;
    align-items: center;
    font-size: 25px;
    color: white;
}

.form {
    font-size: 30px;
    padding: 15px;
}

.formitem {
    width: 100%;
    text-align: left;
    font-weight: 600;
    margin-left: 25px;
}

/deep/.el-divider--horizontal {
    display: block;
    height: 1px;
    width: 100%;
    margin: 5px 0;
}

.tableplay {
    margin-left: 8px;
    color: rgb(26, 115, 232);
    font-size: 14px;
    cursor: pointer;
    text-decoration: underline;
}

.tableplay:hover {
    color: rgb(82, 142, 255);
}

.pic {
    border: 2px solid rgb(36, 104, 242);
    cursor: pointer;
}

.chose {
    border: 2px solid red;
}
</style>