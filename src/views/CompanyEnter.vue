<template>
    <div class="background">
        <div class="mainblock"
            :class="{ 'mainblockheight1': line.left == '50%', 'mainblockheight2': line.left == '0' }">
            <div class="top">
                <div @click="change('0')" :class="{ 'topitemchoice': line.left == '0' }" class="topitem"
                    style="border-radius: 20px 0 0 0;">入驻办理</div>
                <div @click="change('50%')" :class="{ 'topitemchoice': line.left == '50%' }" class="topitem"
                    style="border-radius: 0 20px 0 0;">办理查询</div>
                <div :style="line"></div>
            </div>
            <div v-if="line.left == '0'" class="enterform">
                <el-form ref="enterform" :model="enterform">
                    <el-form-item label-width="0" prop="companyName">
                        <el-input size="small" placeholder="请输入企业名称" v-model="enterform.companyName">
                            <template slot="prepend">企业名称<i class="el-icon-office-building"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item label-width="0" prop="enterCompanyNumber">
                        <el-input size="small" placeholder="请输入企业统一社会信用代码" v-model="enterform.enterCompanyNumber">
                            <template slot="prepend">企业统一社会信用代码<i class="el-icon-office-building"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item label-width="0" prop="enterPhoneNumber">
                        <el-input size="small" placeholder="请输入注册人联系方式" v-model="enterform.enterPhoneNumber">
                            <template slot="prepend">联系方式<i class="el-icon-office-building"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item label-width="0" prop="enterReason">
                        <el-input type="textarea" size="small" placeholder="请输入入驻原因" v-model="enterform.enterReason">
                            <template slot="prepend">入驻原因<i class="el-icon-office-building"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item label-width="0" prop="position">
                        <el-input size="small" placeholder="请输入企业联系人职位" v-model="enterform.position">
                            <template slot="prepend">联系人职位<i class="el-icon-office-building"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item label-width="0" prop="teamSize">
                        <el-input size="small" placeholder="请输入入驻团队规模" v-model="enterform.teamSize">
                            <template slot="prepend">入驻团队规模<i class="el-icon-office-building"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item label-width="0" prop="files">
                        <div style="display: flex;justify-content: space-around;">
                            <el-upload ref="upload" :file-list="enterform.files" multiple action="" :auto-upload="false"
                                :accept="'.bmp,.jpg,.jpeg,.png'" :on-change="filecheck" :on-success="uploadsuccess"
                                :on-error="uploaderror" :on-remove="uploadremove">
                                <el-button slot="trigger" size="small" type="primary">选取文件</el-button>
                                <el-tooltip placement="top-start">
                                    <div slot="content">
                                        <span>只能上传图片，需包含公司信用报告、公司盖章、税务登记证、营业执照等资料</span>
                                    </div>
                                    <i style="cursor: pointer;" class="el-icon-info"></i>
                                </el-tooltip>
                            </el-upload>
                            <el-button @click="enterform_submit" size="small" type="primary">提交材料</el-button>
                        </div>
                    </el-form-item>
                </el-form>
            </div>
            <div v-if="line.left == '50%'" class="selectform">
                <el-form ref="selectform" :model="selectform" :rules="selectformrule">
                    <el-form-item label-width="0" prop="companyNumber">
                        <el-input size="small" placeholder="请输入企业统一社会信用代码" v-model="selectform.companyNumber">
                            <template slot="prepend">统一社会信用代码<i class="el-icon-office-building"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item label-width="0" prop="phoneNumber">
                        <el-input size="small" placeholder="请输入办理人手机号" v-model="selectform.phoneNumber">
                            <template slot="prepend">办理人手机号<i class="el-icon-mobile-phone"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item>
                        <el-button @click="selectform_submit" type="primary"
                            style="font-size: 20px;width: 40%;">查询</el-button>
                    </el-form-item>
                    <el-form-item v-if="selectvis">
                        <div v-if="platformmanager.error === ''"
                            style="display: flex;flex-direction: column;align-items: center;">
                            <span style="font-size: 20px;">账号:{{ platformmanager.number }}</span>
                            <span style="font-size: 20px;">密码:{{ platformmanager.password }}</span>
                            <span @click="$router.push('/login')"
                                style="color: rgb(36, 104, 242);text-decoration: underline;cursor: pointer;">去登录-></span>
                        </div>
                        <div v-else>
                            <span style="font-size: 20px;">失败原因:{{ platformmanager.error }}</span>
                        </div>
                    </el-form-item>
                </el-form>
            </div>
            <span @click="$router.push('/')"
                style="color: rgb(36, 104, 242);text-decoration: underline;cursor: pointer;">
                返回首页
            </span>
        </div>
    </div>
</template>
<script>
import axios from 'axios'
export default {
    data() {
        return {
            enterform: {
                companyName: "",
                enterCompanyNumber: "",
                enterPhoneNumber: "",
                enterReason: "",
                position: "",
                teamSize: "",
                files: []  //公司信用报告、公司盖章、税务登记证、营业执照
            },
            enterformrule: {
                companyName: [
                    { required: true, message: "请输入公司名称", trigger: 'blur' }
                ],
                enterPhoneNumber: [
                    { required: true, message: "请填写联系人联系方式", trigger: 'blur' }
                ],
                enterCompanyNumber: [
                    { required: true, message: "请输入统一社会信用代码", trigger: 'blur' }
                ],
                position: [
                    { required: true, message: "请输入联系人职位", trigger: 'blur' }
                ],
                teamSize: [
                    { required: true, message: "请输入入驻团队规模", trigger: 'blur' }
                ],
                enterReason: [
                    { required: true, message: "请输入入驻原因", trigger: 'blur' }
                ],
                files: []
            },
            selectvis: false,
            platformmanager: {
                number: "",
                password: "",
                error: ""
            },
            selectform: {
                companyNumber: "",
                phoneNumber: ""
            },
            selectformrule: {
                phoneNumber: [
                    { required: true, message: "请输入手机号", trigger: 'blur' }
                ],
                companyNumber: [
                    { required: true, message: "请输入统一社会信用代码", trigger: 'blur' }
                ]
            },
            line: {
                width: '50%',
                height: '1px',
                backgroundColor: "rgb(36,104,242)",
                position: 'absolute',
                bottom: '0',
                left: "0",
                transition: "all 0.5s"
            }
        }
    },
    watch: {
        'line.left': {
            handler(oldvalue) {
                if (oldvalue === '0') {
                    this.enterform = {
                        companyName: "",
                        enterCompanyNumber: "",
                        enterPhoneNumber: "",
                        enterReason: "",
                        position: "",
                        teamSize: "",
                        files: []  //公司信用报告、公司盖章、税务登记证、营业执照
                    }
                } else {
                    this.selectform = {
                        companyNumber: "",
                        phoneNumber: ""
                    }
                }
            },
            deep: true
        }
    },
    methods: {
        filecheck(file) {
            if (file.size / 1024 / 1024 > 14) {
                this.$message({ type: "warning", message: file.name + "上传文件大小不能超过14MB" })
                this.$refs.upload.onRemove(file)
                //console.log(this.dataset.file);
            } else {
                //console.log(file.raw);
                this.enterform.files.push(file.raw)
                console.log(this.enterform.files);
            }
        },
        uploadsuccess() {
            this.enterform.files = []
            console.log("成功");
        },
        uploaderror() {

        },
        uploadremove(file) {
            console.log(file);
            this.enterform.files = this.enterform.files.filter(item => {
                return item.name !== file.name
            })
        },
        selectform_submit() {
            this.$refs.selectform.validate((valid) => {
                if (valid) {
                    //写请求
                    axios.post("http://120.26.142.114:10010/users/company/get/pass/progress", { registrationNumber: this.selectform.companyNumber, phoneNumber: this.selectform.phoneNumber })
                        .then(res => {
                            console.log(res.data);
                            if (res.data.code === 200) {

                                this.platformmanager.number = res.data.data.account
                                this.platformmanager.password = '123456'
                                this.selectform = {
                                    companyNumber: "",
                                    phoneNumber: ""
                                }
                            } else if (res.data.code === 9999) {
                                this.platformmanager.error = res.data.msg
                            } else if (res.data.code === 8546) {
                                this.platformmanager.error = res.data.data
                            } else if (res.data.code === 8545) {
                                this.$message.warning(res.data.msg)
                                return
                            }
                            this.selectvis = true
                        })
                        .catch(e => {
                            console.log(e);
                        })
                } else {
                    return false;
                }
            });
        },
        enterform_submit() {
            let files = new FormData()
            this.enterform.files.forEach(item => {
                files.append("files", item)
            })
            let form = this.enterform
            axios.post(`http://120.26.142.114:10010/users/company/enroll?companyName=${form.companyName}&registrationNumber=${form.enterCompanyNumber}&phoneNumber=${form.enterPhoneNumber}&reason=${form.enterReason}&position=${form.position}&teamSize=${form.teamSize}`, files)
                .then(res => {
                    console.log(res.data);
                    if (res.data.code === 200) {
                        this.$message.success(res.data.msg)
                        this.enterform = {
                            companyName: "",
                            enterCompanyNumber: "",
                            enterPhoneNumber: "",
                            enterReason: "",
                            position: "",
                            teamSize: "",
                            files: []  //公司信用报告、公司盖章、税务登记证、营业执照
                        }
                    } else if (res.data.code === 10203) {
                        this.$message.error(res.data.msg)
                    }
                })
                .catch(e => {
                    console.log(e);
                })
        },
        change(item) {
            setTimeout(() => {
                this.line.left = item
            }, 50)
        }
    }
}
</script>

<style scoped>
.background {
    width: 100%;
    height: 100%;
    background-image: url('../../public/门户网站v1/服务优势背景.png');
    background-repeat: no-repeat;
    background-size: 100% 100%;
    display: flex;
    justify-content: center;
    align-items: center;
}

.mainblock {
    width: 25%;
    background-color: rgba(255, 255, 255, 0.5);
    border-radius: 20px;
}

.mainblockheight1 {
    height: 58%;
}

.mainblockheight2 {
    height: 75%;
}

.top {
    width: 100%;
    height: 15%;
    border-radius: 20px 20px 0 0;
    display: flex;
    justify-content: space-around;
    position: relative;
}

.topitem {
    cursor: pointer;
    width: 50%;
    font-size: 24px;
    background-color: rgba(121, 121, 121, 0.2);
    display: flex;
    flex-direction: column;
    justify-content: center;
}

.topitemchoice {
    color: rgb(36, 104, 242);
    background-color: rgba(121, 121, 121, 0.4);
}

.selectform {
    display: flex;
    flex-direction: column;
    justify-content: space-around;
    align-items: center;
    width: 100%;
    padding-bottom: 0;
    padding-top: 15px;
}

.enterform {
    display: flex;
    flex-direction: column;
    justify-content: space-around;
    align-items: center;
    width: 100%;
    padding-bottom: 0;
    padding-top: 15px;
}
</style>