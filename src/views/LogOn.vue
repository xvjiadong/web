<template>
    <div class="main">
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
                    <el-input size="small" v-model="user.checkpass" style="width: 90%" placeholder="请确认密码">
                        <template slot="prepend">确认密码<i class="el-icon-office-building"></i></template>
                    </el-input>
                </el-form-item>
                <el-form-item prop="email">
                    <el-input size="small" v-model="user.email" style="width: 100%" placeholder="请输入邮箱">
                        <template slot="prepend">邮箱<i class="el-icon-message"></i></template>
                    </el-input>
                </el-form-item>
                <el-form-item>
                    <el-button @click="logon">注册</el-button>
                </el-form-item>
            </el-form>
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
                    axios.post("http://192.168.224.150:10010/users/logon", this.user).then((res) => {
                        if (res.data.code === 200) {
                            this.$message({message:"注册成功",type:"success"})
                            setTimeout(() => {
                                this.$router.push({
                                    path: '/',
                                    query: {
                                        msg: { logonfrom:true,ID: res.data.worknumber }
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
    background-image: url("/public/login.jpg");
    background-size: 100% 100%;
    background-repeat: no-repeat;
    height: 100%;
    width: 100%;
    min-width: 100%;
    min-height: 100%;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}

.block {
    width: 28%;
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
</style>