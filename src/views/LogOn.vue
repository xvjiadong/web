<template>
    <div class="main">
        <div
            style="height: 100%;width: 70%;background-image: url('登录.jpg');text-align: left;display: flex;flex-direction: column;">
            <span
                style="color: rgb(39,46,62);font-size: 28px;font-weight: 600;letter-spacing: 8px;padding: 50px;">数据标注平台</span>
            <span
                style="color: rgb(120,127,142);font-size: 18px;font-weight: 600;letter-spacing: 6px;padding-left: 50px;">为数字化转型提供安全、稳定、灵活的额数字化底座，为智能化审计提供领先的创新技术和平台，助力数字化转型和智能化升级一步到位</span>
        </div>
        <div
            style="width: 30%;height: 100%;display: flex;justify-content: center;align-items: center;flex-direction: column;">
            <span style="color: rgb(39,46,62);font-weight: 600;font-size: 24px;">欢迎注册平台账号</span>
            <div style="width: 65%;"><el-divider></el-divider></div>
            <div style="color: rgb(36,104,242);cursor: pointer;margin-bottom: 15px;font-size: 12px;"
                @click="$router.push('/login')">立即登录</div>
            <div class="block">
                <el-form :model="user" :rules="userrules" status-icon ref="userform" class="userform">
                    <el-form-item prop="name">
                        <el-input size="small" v-model="user.name" style="width: 100%" placeholder="请输入用户名">
                            <template slot="prepend">姓名<i class="el-icon-user"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item prop="phonenumber">
                        <el-input size="small" v-model="user.phonenumber" style="width: 100%" placeholder="请输入手机号">
                            <template slot="prepend">手机号<i class="el-icon-phone"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item prop="password">
                        <el-input size="small" v-model="user.password" style="width: 100%" placeholder="请输入密码">
                            <template slot="prepend">密码<i class="el-icon-mobile"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item prop="checkpass">
                        <el-input size="small" v-model="user.checkpass" style="width: 100%" placeholder="请确认密码">
                            <template slot="prepend">确认密码<i class="el-icon-office-building"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item prop="email">
                        <el-input size="small" v-model="user.email" style="width: 100%" placeholder="请输入邮箱">
                            <template slot="prepend">邮箱<i class="el-icon-message"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item style="margin-bottom: 0;">
                        <el-checkbox v-model="check"> 我已阅读并同意<span style="color: rgb(36,104,242);"
                                @click="noticevisible = true">服务协议，订购协议、隐私政策</span></el-checkbox>
                    </el-form-item>
                </el-form>
                <div style="width: 65%;"><el-divider></el-divider></div>
                <div style="width: 65%;"><el-button :disabled="!check" round
                        style="height: 80%;width: 90%;font-size: 20px;display: flex;justify-content: center;align-items: center;"
                        type="primary" @click="logon">注册</el-button></div>
            </div>
            <el-dialog top="15%" title="注册协议" :visible.sync="noticevisible">
                <div style="height: 200px;overflow-y: auto;word-break: keep-all;text-align: left;">
                    数据标注平台的数据协议

                    数据所有权：数据的所有权归属于数据提供方，数据标注平台在使用数据时应遵守相应的法律法规。

                    数据保密：数据标注平台应对数据提供方的数据进行保密，不得将数据泄露给任何第三方。

                    数据使用目的：数据标注平台只能将数据用于标注任务和训练模型等与数据提供方约定的目的，不得将数据用于其他商业用途或传播给未经授权的人员。

                    标注结果归属：标注结果的知识产权归属于数据提供方，数据标注平台不得将标注结果用于其他用途，也不得将标注结果提供给未经授权的人员。

                    数据安全：数据标注平台应采取合理的安全措施，保护数据的安全性和完整性，防止数据被非法获取、篡改或丢失。

                    数据质量：数据标注平台应确保标注人员按照约定的标准进行标注，提供高质量的标注结果。

                    数据备份：数据标注平台应定期对数据进行备份，以防止数据丢失或损坏。

                    合作终止：当双 方合作结束时，数据标注平台应将所有数据和相关信息交还给数据提供方，并删除或销毁与数据提供方相关的数据副本。

                    违约责任：如果数据标注平台违反协议约定，导致数据提供方遭受损失，数据标注平台应承担相应的法律责任。

                    法律适用和争议解决：本协议适用于中华人民共和国的法律，并在发生争议时，双方应通过友好协商解决。如协商不成，应提交有管辖权的人民法院解决。

                    以上为数据标注平台的数据协议，双方应严格遵守并履行协议中的各项约定。
                </div>
            </el-dialog>
        </div>

    </div>
</template>
<script>
import axios from 'axios'
export default {
    mounted() {
    },
    data() {
        let validatename = (rule, value, callback) => {
            if (value === "") {
                return callback(new Error('请输入姓名'));
            } else {
                callback()
            }
        };
        let validatepassword = (rule, value, callback) => {
            let a = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d]{6,18}$/
            if (value === '') {
                return callback(new Error('请输入密码'));
            } else if (!a.test(value)) {
                return callback(new Error('密码为6-18位，包含大写字母、小写字母和数字'));
            } else {
                callback()
            }
        };
        let validatecheckpass = (rule, value, callback) => {
            if (value === "") {
                return callback(new Error('请再次输入密码'));
            } else if (value !== this.user.password) {
                return callback(new Error("密码不相同"))
            } else {
                callback()
            }
        };
        let validatephonenumber = (rule, value, callback) => {
            if (value === '') {
                return callback(new Error('请输入手机号'));
            } else {
                callback()
            }
        };
        let validateemail = (rule, value, callback) => {
            let a = /^([a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(.[a-zA-Z0-9_-])+/
            if (value === '') {
                return callback(new Error('请输入邮箱'));
            } else if (!a.test(value)) {
                return callback(new Error('非法邮箱格式'));
            } else {
                callback()
            }
        };
        return {
            user: {
                password: "",
                checkpass: "",
                phonenumber: "",
                name: "",
                email: "",
            },
            check: false,
            noticevisible: false,
            userrules: {
                name: [
                    { validator: validatename, trigger: 'blur' }
                ],
                password: [
                    { validator: validatepassword, trigger: 'blur' }
                ],
                checkpass: [
                    { validator: validatecheckpass, trigger: 'blur' }
                ],
                phonenumber: [
                    { validator: validatephonenumber, trigger: 'blur' }
                ],
                email: [
                    { validator: validateemail, trigger: 'blur' }
                ]
            }
        }
    },
    methods: {
        logon() {
            this.$refs.userform.validate((result) => {
                console.log(result);
                if (result) {
                    /*注册请求发送*/
                    axios.post("http://120.26.142.114:10010/users/logon", this.user).then((res) => {
                        if (res.data.code === 200) {
                            this.$message({ message: "注册成功", type: "success" })
                            setTimeout(() => {
                                this.$router.push({
                                    path: '/',
                                    query: {
                                        msg: { logonfrom: true, ID: res.data.worknumber }
                                    }
                                })
                            }, 1000)
                        } else {
                            this.$message({ message: "请重新填写注册信息", type: "error" })
                        }
                    })
                }
            })
        },
    },
    computed: {},
}   
</script>
<style scoped>
.main {
    background-size: 100% 100%;
    background-repeat: no-repeat;
    height: 100%;
    width: 100%;
    min-width: 100%;
    min-height: 100%;
    display: flex;
    align-items: center;
}

.block {
    width: 100%;
    height: 55%;
    border-radius: 15px;
    background-color: rgba(255, 255, 255, 0.5);
    display: flex;
    flex-direction: column;
    justify-content: space-around;
    align-items: center;
}

.userform {
    display: flex;
    flex-direction: column;
    justify-content: space-around;
    align-items: center;
    width: 90%;
    padding: 15px;
}

/deep/.el-divider--horizontal {
    display: block;
    height: 1px;
    width: 100%;
    margin: 5px 0;
}
</style>