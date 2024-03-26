<template>
    <div class="main">
        <div
            style="height: 100%;width: 70%;background-image: url('登录.jpg');text-align: left;display: flex;flex-direction: column;">
            <span @click="$router.push('/')"
                style="cursor: pointer;color: rgb(39,46,62);font-size: 28px;font-weight: 600;letter-spacing: 8px;padding:50px;">数据标注平台</span>
            <span
                style="color: rgb(120,127,142);font-size: 18px;font-weight: 600;letter-spacing: 6px;padding-left: 50px;">为数字化转型提供安全、稳定、灵活的额数字化底座，为智能化审计提供领先的创新技术和平台，助力数字化转型和智能化升级一步到位</span>
        </div>
        <div
            style="width: 30%;height: 100%;display: flex;justify-content: center;align-items: center;flex-direction: column;">
            <span style="color: rgb(39,46,62);font-weight: 600;font-size: 24px;">欢迎登陆平台</span>
            <div style="width: 65%;"><el-divider></el-divider></div>
            <div class="block">
                <el-form status-icon ref="userform" :model="user" :rules="userrules" class="userform">
                    <el-form-item prop="phoneNumber">
                        <el-input v-model="user.phoneNumber" size="small" placeholder="请输入工号">
                            <template slot="prepend">工号<i class="el-icon-user"></i></template>
                        </el-input>
                    </el-form-item>
                    <el-form-item prop="password">
                        <el-input v-model="user.password" type="password" size="small" placeholder="请输入密码">
                            <template slot="prepend">密码<i class="el-icon-mobile"></i></template>
                        </el-input>
                    </el-form-item>
                </el-form>
            </div>
            <div style="width: 60%;"><el-button round type="primary"
                    style="color:white;width: 100%;font-size: 18px;height: 80%;display: flex;justify-content: center;align-items: center;"
                    @click="SubForm('userform')">登录</el-button> </div>
            <div style="width: 65%;"><el-divider></el-divider></div>
            <div style="width: 65%; display: flex;justify-content: space-around;color: rgb(215,216,217);">
                <span style="cursor: pointer;color: rgb(100,100,101);">忘记密码</span>
                <span style="cursor: pointer;color: rgb(100,100,101);" @click="logon">注册账号</span>
            </div>
        </div>
    </div>
</template>
<script>
import axios from 'axios'
axios.defaults.timeout = 50000
export default {
    mounted() {
        if (this.$route.query.msg) {
            this.user.worknumber = this.$route.query.msg.ID
        }
    },
    data() {
        let validateworknumber = (rule, value, callback) => {
            if (value === "") {
                return callback(new Error('工号不能为空'));
            } else {
                callback()
            }
        };
        let validatepassword = (rule, value, callback) => {
            if (value === '') {
                return callback(new Error('密码不能为空'));
            } else {
                callback()
            }
        };
        return {
            user: {
                phoneNumber: "",
                password: ""
            },
            userrules: {
                phoneNumber: [
                    { validator: validateworknumber, trigger: 'blur' }
                ],
                password: [
                    { validator: validatepassword, trigger: 'blur' }
                ]
            }
        }
    },
    methods: {
        SubForm(item) {
            this.$refs[item].validate((result) => {
                if (result) {
                    //console.log(JSON.stringify(this.user));
                    axios.post("http://120.26.142.114:10010/users/login", this.user).then((res) => {
                        if (res.data.code === 200) {
                            this.$store.commit("setuser", res.data.data)
                            this.$store.commit("changeisadd", false)
                            //console.log(this.$store.state.user);
                            this.$message({ message: "登录成功", type: "success" })
                            this.$router.push('/MainBox')
                        } else {
                            this.$message({ message: "请重新输入工号密码", type: "error" })
                        }
                    })
                }
            })
        },
        logon() {
            this.$router.push("/logon")
        }
    }
}
</script>
<style scoped>
.main {
    width: 100%;
    height: 100%;
    margin: 0;
    padding: 0;
    display: flex;
    align-items: center;
    background-repeat: no-repeat;
    background-size: 100% 100%;
}

.block {
    background-color: rgba(255, 255, 255, 0.6);
    display: flex;
    justify-content: center;
    align-items: center;
    width: 98%;
    height: 20%;
    border-radius: 15px;
}

.userform {
    display: flex;
    flex-direction: column;
    justify-content: space-around;
    align-items: center;
    width: 100%;
    padding: 15px;
    padding-bottom: 0;
}

/deep/.el-divider--horizontal {
    display: block;
    height: 1px;
    width: 100%;
    margin: 5px 0;
}
</style>