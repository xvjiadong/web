<template>
    <div class="main">
        <div class="block">
            <el-form status-icon ref="userform" :model="user" :rules="userrules" class="userform">
                <el-form-item prop="username">
                    <el-input v-model="user.username" size="small" placeholder="请输入工号">
                        <template slot="prepend">工号<i class="el-icon-user"></i></template>
                    </el-input>
                </el-form-item>
                <el-form-item prop="password">
                    <el-input v-model="user.password" type="password" size="small" placeholder="请输入密码">
                        <template slot="prepend">密码<i class="el-icon-mobile"></i></template>
                    </el-input>
                </el-form-item>
                <el-form-item>
                    <el-button @click="SubForm('userform')">登录</el-button>
                    <el-button @click="logon">注册</el-button>
                </el-form-item>
            </el-form>
        </div>
    </div>
</template>
<script>
import axios from 'axios'
axios.defaults.timeout=50000
export default {
    mounted() {
        if (this.$route.query.msg) {
            this.user.worknumber=this.$route.query.msg.ID
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
                username: "",
                password: ""
            },
            userrules: {
                username: [
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
                    axios.post("http://192.168.224.150:10010/users/login", this.user).then((res) => {
                        console.log(res.data);
                        if (res.data.code === 200) {
                            this.$store.commit("setuser", res.data.user)
                            this.$store.commit("changeisadd", false)
                            //console.log(this.$store.state.user);
                            this.$message({ message: "登录成功", type: "success" })
                            this.$router.push({ path: '/MainBox' })
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
    justify-content: center;
    align-items: center;
    background-image: url("/public/login.jpg");
    background-repeat: no-repeat;
    background-size: 100% 100%;
}

.block {
    background-color: rgba(255, 255, 255, 0.6);
    display: flex;
    justify-content: center;
    align-items: center;
    width: 25%;
    height: 35%;
    border-radius: 15px;
}

.userform {
    display: flex;
    flex-direction: column;
    justify-content: space-around;
    align-items: center;
    width: 80%;
    padding: 15px;
}
</style>