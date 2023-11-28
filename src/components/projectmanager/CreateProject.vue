<template>
    <div style="width: 95%;">
        <div class="step">
            <div style="width: 60%;">
                <el-steps :active="active" finish-status="success" align-center process-status="finish" space="100%">
                    <el-step title="创建项目" icon="el-icon-edit"></el-step>
                    <el-step title="导入待标注文件" icon="el-icon-upload"></el-step>
                </el-steps>
            </div>
        </div>
        <el-card :class="{ boxCard1: $store.state.islight, boxCard2: !$store.state.islight }" v-if="active == 0">
            <div slot="header" :class="{ cardheader: $store.state.islight, cardheader2: !$store.state.islight }">
                <span>基本信息</span>
            </div>
            <el-form ref="form1" :model="dataset" :rules="datasetrule" label-width="100px" class="form"
                label-position="left">
                <el-form-item prop="name" label="数据集名称:" class="formitem">
                    <el-input style="width: 60%;" size="mini" v-model="dataset.name" placeholder="限制50个字符以内,支持汉字、大小写英文、数字"
                        maxlength="50" show-word-limit></el-input>
                </el-form-item>
                <el-form-item prop="datatype" label="数据类型:" class="formitem">
                    <el-radio-group v-model="dataset.datatype" size="small">
                        <el-radio-button label="图像"></el-radio-button>
                        <el-radio-button label="文本"></el-radio-button>
                    </el-radio-group>
                </el-form-item>
                <el-form-item prop="version" label="数据集版本:" class="formitem version">
                    <span :style="$store.state.islight ? { color: 'black' } : { color: 'rgb(96,98,102)' }">{{
                        dataset.version
                    }}</span>
                </el-form-item>
                <el-form-item prop="marktype" label="标注类型" class="formitem">
                    <el-select filterable="" v-model="dataset.marktype" size="small" :disabled="dataset.datatype === ''">
                        <el-option v-for="item in marktypelist" :key="item.value" :value="item.value" :label="item.label">
                        </el-option>
                    </el-select>
                </el-form-item>
                <el-form-item class="formitem" label-width="0">
                    <el-button size="small" type="primary" @click="complete1">完成创建并上传</el-button>
                    <el-button size="small" @click="jump">取消</el-button>
                </el-form-item>
            </el-form>

        </el-card>
        <el-card :class="{ boxCard1: $store.state.islight, boxCard2: !$store.state.islight }" v-if="active == 1">
            <div slot="header" class="cardheader">
                <el-page-header @back="goBack" content="导入配置">
                </el-page-header>
            </div>
            <el-form ref="form2" :model="dataset" :rules="datasetrule2" label-width="110px" class="form"
                label-position="left">
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
                    <el-progress v-if="uploadProgress >= 0" :percentage="uploadProgress" :format="format"></el-progress>
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
import axios from 'axios'
export default {
    name: "CreateProject",
    components: {

    },
    data() {
        let validatename = (rule, value, callback) => {
            if (value === "") {
                return callback(new Error('名称不能为空'));
            } else if (!/^[\u4e00-\u9fa5a-zA-Z0-9][\u4e00-\u9fa5a-zA-Z0-9_]{0,49}$/.test(value)) {
                return callback(new Error('项目名称仅支持中文、英文、数字'));
            } else {
                callback()
            }
        };
        let validatedatatype = (rule, value, callback) => {
            if (value === '') {
                return callback(new Error('请选择数据类型'));
            } else {
                callback()
            }
        };
        let validatemarktype = (rule, value, callback) => {
            if (value === '') {
                return callback(new Error('请选择标注任务类型'));
            } else {
                callback()
            }
        };
        let validateismarked = (rule, value, callback) => {
            if (value === "") {
                return callback(new Error('请选择数据集标注状态'));
            } else {
                callback()
            }
        };
        let validatefile = (rule, value, callback) => {
            if (value.length === 0) {
                return callback(new Error('请上传至少一份数据'));
            } else {
                callback()
            }
        };
        let validatelink = (rule, value, callback) => {
            if (this.dataset.inputway === "分享链接导入") {
                if (value === '') {
                    return callback(new Error('分享链接不能为空'));
                } else {
                    callback()
                }
            } else if (this.dataset.inputway2 === "平台已有数据集") {
                return callback(new Error('请选择已有数据集'));
            }
            else {
                callback()
            }

        };
        let validateinputway = (rule, value, callback) => {
            if (value === '') {
                return callback(new Error('请选择数据导入方式'));
            } else {
                callback()
            }
        };
        let validateinputway2 = (rule, value, callback) => {
            if (value === '') {
                return callback(new Error('请选择本地导入方式'));
            } else {
                callback()
            }
        };
        return {
            active: 0,
            dataset: {
                name: "",
                datatype: "",
                version: "V1",
                marktype: "",
                file: [],
                ismarked: false,
                inputway: "",
                inputway2: "",
                link: "",
                uploadProgress: -1
            },
            datasetrule: {
                name: [
                    { required: true, validator: validatename, trigger: 'blur' }
                ],
                datatype: [
                    { required: true, validator: validatedatatype, trigger: 'blur' }
                ],
                marktype: [
                    { required: true, validator: validatemarktype, trigger: 'blur' }
                ]
            },
            datasetrule2: {
                ismarked: [
                    { required: true, validator: validateismarked, trigger: 'blur' }
                ],
                file: [
                    { required: true, validator: validatefile, trigger: 'blur' }
                ],
                link: [
                    { validator: validatelink, trigger: 'blur' }
                ],
                inputway: [
                    { required: true, validator: validateinputway, trigger: 'blur' }
                ],
                inputway2: [
                    { validator: validateinputway2, trigger: 'blur' }
                ]
            },
            input: [{ value: "本地导入", label: "本地导入" }, { value: "平台已有数据集", label: "平台已有数据集" }, { value: "分享链接导入", label: "分享链接导入" }],
            addlink: [{ value: "9878", }]
        }
    },
    computed: {
        marktypelist() {
            let a = [{ value: "图像文本标注", label: "图像文本标注" },{ value: "图片分类标注", label: "图片分类标注" }, { value: "多边形标注", label: "多边形标注" }, { value: "文本检测", label: "文本检测" }, { value: "点标注", label: "点标注" }, { value: "线标注", label: "线标注" }, { value: "混合标注", label: "混合标注" }]
            let b = [{ value: "关系抽取", label: "关系抽取" }, { value: "证据划选", label: "证据划选" }, { value: "实体抽取", label: "实体抽取" }, { value: "混合标注", label: "混合标注" }, { value: "文本分类标注", label: "文本分类标注" }, { value: "信息抽取标注", label: "信息抽取标注" }]
            if (this.dataset.datatype === "图像") {
                return a
            } else if (this.dataset.datatype === "文本") {
                return b
            }
            return []
        },
        uploadway() {
            let a = [{ value: "上传压缩包", label: "上传压缩包" }, { value: "上传PDF", label: "上传PDF" }, { value: "上传docx", label: "上传docx" }, { value: "上传txt", label: "上传txt" }]
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
            } else if (this.dataset.inputway2 === "上传txt") {
                return "上传txt:"
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
            } else if (this.uploadlabel === "上传txt:") {
                return ".txt"
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
        format(percentage) {
            return percentage === 100 ? '满' : `${percentage}%`;
        },
        goBack() {
            this.active -= 1
            this.dataset.name = ""
            this.dataset.datatype = "",
                this.dataset.version = "v1",
                this.dataset.marktype = "",
                this.dataset.file = [],
                this.dataset.ismarke = false,
                this.dataset.inputway = "",
                this.dataset.inputway2 = "",
                this.dataset.link = ""

        },
        jump() {
            this.$router.push("/ProjectList")
        },
        complete1() {
            this.$refs.form1.validate((result) => {
                if (result) {
                    this.active += 1
                }
            })
        },
        complete2() {
            this.$refs.form2.validate((result) => {
                console.log(result);
                let uploadform = {}
                uploadform.name = this.dataset.name
                uploadform.dataType = this.dataset.datatype
                uploadform.markType = this.dataset.marktype
                uploadform.version = this.dataset.version
                //uploadform.append("inputway", this.dataset.inputway)
                /*if (this.dataset.inputway === "本地导入") {
                    this.dataset.file.forEach(item => {
                        uploadform.append("file", item.raw)
                    })
                } else {
                    uploadform.set("file", this.dataset.link)
                }*/
                axios.post("http://192.168.224.150:10010/items", uploadform).then((res) => {
                    console.log(res.data);
                    if (res.data.code === 200) {
                        let file = new FormData()
                        if (this.dataset.inputway === "本地导入") {
                            this.dataset.file.forEach(item => {
                                file.append("file", item.raw)
                            })
                        } else {
                            file.set("file", this.dataset.link)
                        }
                        file.append("version", this.dataset.version)
                        file.append("id", res.data.data)
                        if (this.dataset.inputway2 === "上传图片") {
                            axios.post("http://192.168.224.150:10010/items/image", file, { headers: { "Content-Type": "multipart/form-data" } }, {
                                onUploadProgress: progress => {
                                    this.uploadProgress = Number(
                                        ((progress.loaded / progress.total) * 100).toFixed(2)
                                    )
                                }
                            }).then((res2) => {
                                console.log(res2.data);
                                this.$message({ type: 'success', message: "创建项目成功" })
                                setTimeout(() => {
                                    this.active += 1
                                    this.$router.push("/Projectlist")
                                }, 1000);
                            })
                        } else if (this.dataset.inputway2 === "上传docx") {
                            axios.post("http://192.168.224.150:10010/items/docx", file, { headers: { "Content-Type": "multipart/form-data" } }, {
                                onUploadProgress: progress => {
                                    this.uploadProgress = Number(
                                        ((progress.loaded / progress.total) * 100).toFixed(2)
                                    )
                                }
                            }).then((res2) => {
                                console.log(res2.data);
                                this.$message({ type: 'success', message: "创建项目成功" })
                                setTimeout(() => {
                                    this.active += 1
                                    this.$router.push("/Projectlist")
                                }, 1000);
                            })
                        } else if (this.dataset.inputway2 === "上传PDF") {
                            axios.post("http://192.168.224.150:10010/items/pdf", file, { headers: { "Content-Type": "multipart/form-data" } }, {
                                onUploadProgress: progress => {
                                    this.uploadProgress = Number(
                                        ((progress.loaded / progress.total) * 100).toFixed(2)
                                    )
                                }
                            }).then((res2) => {
                                console.log(res2.data);
                                this.$message({ type: 'success', message: "创建项目成功" })
                                setTimeout(() => {
                                    this.active += 1
                                    this.$router.push("/Projectlist")
                                }, 1000);
                            })
                        } else if (this.dataset.inputway2 === "上传txt") {
                            axios.post("http://192.168.224.150:10010/items/txt", file, { headers: { "Content-Type": "multipart/form-data" } }, {
                                onUploadProgress: progress => {
                                    this.uploadProgress = Number(
                                        ((progress.loaded / progress.total) * 100).toFixed(2)
                                    )
                                }
                            }).then((res2) => {
                                console.log(res2.data);
                                this.$message({ type: 'success', message: "创建项目成功" })
                                setTimeout(() => {
                                    this.active += 1
                                    this.$router.push("/Projectlist")
                                }, 1000);
                            })
                        }
                    } else {
                        this.$message({ type: "error", message: "创建失败" })
                    }
                })
            })

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
                //console.log(file.raw);
                this.dataset.file.push(file)
                //console.log(this.dataset.file);
            }
        },
        uploadsuccess() {
            this.dataset.file = []
            console.log("成功");
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
        console.log(this.$route);
    },
}
</script>
<style scoped>
.step {
    width: 100%;
    display: flex;
    align-items: center;
    justify-content: center;
}

.boxCard1 {
    width: 100%;
    margin-left: 1%;
    height: 560px;
    background-color: #fff;
}

.boxCard2 {
    width: 100%;
    margin-left: 1%;
    height: 560px;
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