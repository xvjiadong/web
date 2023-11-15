<template>
    <div style="width: 95%;margin-top: 2%;">
        <el-card class="box-card">
            <div slot="header" class="cardheader">
                <el-page-header @back="goBack" content="导入配置">
                </el-page-header>
            </div>
            <el-form ref="form2" :model="dataset" label-width="110px" class="form" label-position="left">
                <el-form-item label="导入项目版本" class="formitem">
                    <el-select filterable size="mini" v-model="dataset.projectid" placeholder="请选择项目">
                        <el-option v-for="item in projectlist" :key="item.projectid" :label="item.name"
                            :value="item.projectid"></el-option>
                    </el-select>
                    <el-select filterable v-model="dataset.version" size="mini" :disabled="dataset.projectid === ''"
                        style="width: 22%;margin-left: 8px;">
                        <el-option v-for="item in versionlist" :key="item.versionid" :value="item.versionname"
                            :label="`${item.versionname}-${item.marktype}`">
                        </el-option>
                    </el-select>
                </el-form-item>
                <el-form-item prop="ismarked" label="数据标注状态:" class="formitem">
                    <el-radio v-model="dataset.ismarked" :label='true'>有标注信息</el-radio>
                    <el-radio v-model="dataset.ismarked" :label='false'>无标注信息</el-radio>
                </el-form-item>
                <el-form-item prop="inputway" label="导入方式:" class="formitem">
                    <el-select filterable="" v-model="dataset.inputway" size="small">
                        <el-option v-for="item in input" :key="item.value" :value="item.value" :label="item.label">
                        </el-option>
                    </el-select>
                    <el-select v-if="dataset.inputway === '本地导入'" filterable="" v-model="dataset.inputway2" size="small">
                        <el-option v-for="item in uploadway" :key="item.value" :value="item.value" :label="item.label">
                        </el-option>
                    </el-select>
                </el-form-item>
                <el-form-item v-if="dataset.inputway2 !== '' && dataset.inputway === '本地导入'" prop="file"
                    :label="uploadlabel" class="formitem version">
                    <el-upload ref="upload" :file-list="dataset.file" drag multiple action="" :auto-upload="false"
                        :accept="filetype" :on-change="filecheck" :on-success="uploadsuccess" :on-error="uploaderror"
                        :list-type="listType" :on-remove="uploadremove">
                        <div slot="trigger">
                            <i class="el-icon-upload"></i>
                            <div class="el-upload__text">
                                将文件拖到此处，或<em>点击上传</em><br>
                                可接受文件类型:{{ filetype }}
                            </div>
                        </div>
                        <div class="el-upload__tip" slot="tip">文件大小限制在14MB内，请确保文件格式正确</div>
                    </el-upload>
                </el-form-item>
                <el-form-item v-if="dataset.inputway === '分享链接导入' || dataset.inputway === '平台已有数据集'" :label="uploadlabel"
                    class="formitem" prop="link">
                    <el-input style="width: 60%;" v-if="dataset.inputway === '分享链接导入'" size="small" v-model="dataset.link"
                        placeholder="请输入分享链接"></el-input>
                    <el-select v-if="dataset.inputway === '平台已有数据集'" size="small" v-model="dataset.link"
                        placeholder="请选择数据集">
                        <el-option v-for="item in addlink" :key="item.value" :value="item.value"></el-option>
                    </el-select>
                </el-form-item>
                <el-form-item class="formitem" :class="{ pic: listType === 'picture-card' }">
                    <el-button size="small" type="primary" @click="complete2">导入数据集</el-button>
                    <el-button @click="jump">取消</el-button>
                </el-form-item>
            </el-form>
        </el-card>
    </div>
</template>
<script>
export default {
    data() {
        return {
            dataset: {
                datatype: "",
                projectid: "",
                version: "",
                ismarked: false,
                inputway: "",
                inputway2: "",
                file: [],
                link: ""
            },
            input: [{ value: "本地导入", label: "本地导入" }, { value: "平台已有数据集", label: "平台已有数据集" }, { value: "分享链接导入", label: "分享链接导入" }],
            addlink: [{ value: "9878", }],
            projectlist: [
                {
                    projectid: "188865667",     //项目id
                    name: "测试数据1",          //项目名
                    datatype: "图像",          //数据类型
                    version: [                 //下辖版本
                        {
                            versionid: "1697286",      //版本id
                            versionname: "v1",         //版本号
                            versionnumber: "600",      //数据量
                            marktype: "图片分类",      //标注任务类型
                            markprocess: "100%",        //标注进度
                            task: [               //任务
                                {
                                    taskid: "1",       //任务id
                                    taskname: "4848",
                                    tasknumber: "150",   //任务标注数量
                                    taskperson: "测试标注员1",   //任务承担人
                                    taskprocess: "15%",  //任务进度
                                    taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                    taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                    juideprocess: "0%",     //审核进度
                                },
                                {
                                    taskid: "2",       //任务id
                                    taskname: "4848",
                                    tasknumber: "150",   //任务标注数量
                                    taskperson: "测试标注员2",   //任务承担人
                                    taskprocess: "12%",  //任务进度
                                    taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                    taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                    juideprocess: "0%",     //审核进度
                                },
                                {
                                    taskid: "3",       //任务id
                                    taskname: "4848",
                                    tasknumber: "150",   //任务标注数量
                                    taskperson: "测试标注员3",   //任务承担人
                                    taskprocess: "42%",  //任务进度
                                    taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                    taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                    juideprocess: "0%",     //审核进度
                                },
                                {
                                    taskid: "4",       //任务id
                                    taskname: "4848",
                                    tasknumber: "150",   //任务标注数量
                                    taskperson: "测试标注员4",   //任务承担人
                                    taskprocess: "56%",  //任务进度
                                    taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                    taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                    juideprocess: "0%",     //审核进度
                                }
                            ]
                        },
                        {
                            versionid: "1592156",
                            versionname: "v2",
                            versionnumber: "452",
                            datatype: "图像",
                            marktype: "图像文本识别",
                            markprocess: "15%",
                            task: [               //任务
                                {
                                    taskid: "15",       //任务id
                                    taskname: "496",
                                    tasknumber: "150",   //任务标注数量
                                    taskperson: "测试标注员1",   //任务承担人
                                    taskprocess: "15%",  //任务进度
                                    taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                    taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                    juideprocess: "0%",     //审核进度
                                }
                            ]
                        },
                        {
                            versionid: "1578156",
                            versionname: "v3",
                            versionnumber: "452",
                            datatype: "图像",
                            marktype: "图像文本识别",
                            markprocess: "15%",

                        },
                        {
                            versionid: "15598756",
                            versionname: "v4",
                            versionnumber: "452",
                            datatype: "图像",
                            marktype: "图像文本识别",
                            markprocess: "15%",

                        }
                    ]
                },
                {
                    projectid: "595398126",
                    name: "测试数据2",
                    datatype: "文本",
                    version: [
                        {
                            versionid: "79526",
                            versionname: "v1",
                            versionnumber: "456",

                            marktype: "文本分类",
                            markprocess: "15%",

                        },
                        {
                            versionid: "7595",
                            versionname: "v2",
                            versionnumber: "324",
                            datatype: "文本",
                            marktype: "信息抽取标注",
                            markprocess: "78%",

                        }
                    ]
                },
                {
                    projectid: "1",
                    name: "测试数据2",
                    datatype: "文本",
                    version: [
                        {
                            versionid: "926",
                            versionname: "v1",
                            versionnumber: "456",

                            marktype: "文本分类",
                            markprocess: "15%",

                        },
                        {
                            versionid: "59623",
                            versionname: "v2",
                            versionnumber: "324",
                            datatype: "文本",
                            marktype: "信息抽取标注",
                            markprocess: "78%",

                        }
                    ]
                },
                {
                    projectid: "2",
                    name: "测试数据2",
                    datatype: "文本",
                    version: [
                        {
                            versionid: "79kl",
                            versionname: "v1",
                            versionnumber: "456",

                            marktype: "文本分类",
                            markprocess: "15%",

                        },
                        {
                            versionid: "awf",
                            versionname: "v2",
                            versionnumber: "324",
                            datatype: "文本",
                            marktype: "信息抽取标注",
                            markprocess: "78%",

                        }
                    ]
                },
                {
                    projectid: "3",
                    name: "测试数据2",
                    datatype: "文本",
                    version: [
                        {
                            versionid: "79iojk6",
                            versionname: "v1",
                            versionnumber: "456",

                            marktype: "文本分类",
                            markprocess: "15%",

                        },
                        {
                            versionid: "28+95",
                            versionname: "v2",
                            versionnumber: "324",
                            datatype: "文本",
                            marktype: "信息抽取标注",
                            markprocess: "78%",

                        }
                    ]
                },
                {
                    projectid: "4",
                    name: "测试数据2",
                    datatype: "文本",
                    version: [
                        {
                            versionid: "5965mokl",
                            versionname: "v1",
                            versionnumber: "456",

                            marktype: "文本分类",
                            markprocess: "15%",

                        },
                        {
                            versionid: "tyguhj",
                            versionname: "v2",
                            versionnumber: "324",
                            datatype: "文本",
                            marktype: "信息抽取标注",
                            markprocess: "78%",

                        }
                    ]
                },
            ],
        }
    },
    computed: {
        versionlist() {
            if (this.dataset.projectid) {
                return this.projectlist.filter(item => {
                    return item.projectid == this.dataset.projectid
                })[0].version
            }
            return []
        },
        uploadway() {
            let a = [{ value: "上传压缩包", label: "上传压缩包" }, { value: "上传PDF", label: "上传PDF" }, { value: "上传docx", label: "上传docx" }]
            let b = [{ value: "上传压缩包", label: "上传压缩包" }, { value: "上传图片", label: "上传图片" }]
            if (this.dataset.datatype === "文本") {
                return a
            } else if (this.dataset.datatype === "图像") {
                if (this.dataset.ismarked) {
                    return [{ value: "上传压缩包", label: "上传压缩包" }]
                }
                return b
            }
            return []
        },
        uploadlabel() {
            if (this.dataset.inputway === "平台已有数据集") {
                return "选择数据集:"
            } else if (this.dataset.inputway === "分享链接导入") {
                return "链接地址:"
            } else if (this.dataset.inputway2 === "上传压缩包" || this.dataset.ismarked) {
                return "上传压缩包:"
            } else if (this.dataset.inputway2 === "上传PDF") {
                return "上传PDF:"
            } else if (this.dataset.inputway2 === "上传docx") {
                return "上传docx:"
            } else if (this.dataset.inputway2 === "上传图片") {
                return "上传图片:"
            }
            return ""
        },
        filetype() {
            if (this.uploadlabel === "上传压缩包:") {
                return ".zip,.rar,.tar.gz"
            } else if (this.uploadlabel === "上传PDF:") {
                return ".pdf"
            } else if (this.uploadlabel === "上传docx:") {
                return ".docx,.doc"
            } else if (this.uploadlabel === "上传图片:") {
                return ".bmp,.jpg,.jpeg,.png"
            }
            return ""
        },
        listType() {
            if (this.uploadlabel === "上传图片:") {
                return "picture-card"
            }
            return "text"
        }
    },
    watch: {
        'dataset.inputway2': {
            handler() {

                if (this.dataset.file.length > 0) {
                    //this.$refs.upload.clearFiles()
                    this.dataset.file = []
                }
            },
        },
        'dataset.inputway': {
            handler() {
                //console.log(newvalue, oldvalue);
                if (this.dataset.file.length > 0) {
                    //this.$refs.upload.clearFiles()
                    this.dataset.file = []
                }
            },
        },
        'dataset.ismarked': {
            handler() {
                this.dataset.inputway = ""
                this.dataset.inputway2 = ""
                this.dataset.file = []
                //this.$refs.upload.clearFiles()
            },
        },
        'dataset.datatype': {
            handler() {
                this.dataset.marktype = ""
            },
        }
    },
    methods: {
        goBack() {
            this.$router.push("/ProjectList")
        },
        complete2() {
            console.log(this.dataset);
        },
        jump() {
            this.$router.push("/ProjectList")
        },
        filecheck(file) {
            if (file.size / 1024 / 1024 > 14) {
                this.$message({ type: "warning", message: file.name + "上传文件大小不能超过14MB" })
                this.$refs.upload.onRemove(file)
                //console.log(this.dataset.file);
            } else if (!this.filetype.includes(file.name.split(".")[file.name.split(".").length - 1])) {
                this.$message({ type: "warning", message: file.name + "不符合上传格式要求" })
                this.$refs.upload.onRemove(file)
            } else {
                console.log(file.raw);
                this.dataset.file.push(file)
                //console.log(this.dataset.file);
            }
        },
        uploadsuccess() {
            this.dataset.file=[]
        },
        uploaderror() {

        },
        uploadremove(file) {
            console.log(file);
            this.dataset.file = this.dataset.file.filter(item => {
                return item.name !== file.name
            })
        }
    },
    mounted() {
        console.log(this.$route.query);
        let a = this.$route.query
        this.dataset.datatype = a.datatype
        this.dataset.projectid = a.projectid
        this.dataset.version = a.version

    },
}
</script>
<style scoped>
.box-card {
    width: 100%;
    margin-left: 1%;
    height: 600px;
}

.cardheader {
    display: flex;
    justify-content: left;
    padding-left: 15px;
    align-items: center;
    font-size: 25px;
}

.form {
    font-size: 30px;
    padding: 15px;
}

.formitem {
    width: 60%;
    text-align: left;

}

/deep/.el-upload-list {
    margin: 0;
    padding: 0;
    list-style: none;
    position: absolute;
    top: -74%;
    left: 78%;
    height: 220%;
    width: 100%;
    overflow-y: scroll;
}

/deep/.el-upload-list--picture .el-upload-list__item {
    z-index: 0;
    background-color: #fff;
    border: 1px solid #c0ccda;
    border-radius: 6px;
    box-sizing: border-box;
    margin-top: 10px;
    margin-left: 10px;
    margin-bottom: 10px;
    padding: 10px 10px 10px 90px;
    height: 35%;
    float: left;
    width: 35%;
}

/deep/.el-upload--picture-card {
    background-color: #fbfdff;
    border: 1px dashed #c0ccda;
    border-radius: 6px;
    box-sizing: border-box;
    width: 148px;
    height: 148px;
    vertical-align: top;
    line-height: 38px;
}

.pic {
    margin-top: 80px;
}
</style>