<template>
    <div style="width: 97%;margin-top: 30px;">
        <el-card :class="{ boxCard1: $store.state.islight, boxCard2: !$store.state.islight }">
            <div slot="header" :class="{ cardheader: $store.state.islight, cardheader2: !$store.state.islight }">
                <el-page-header @back="goBack" content="个人中心">
                </el-page-header>
            </div>
            <div style="display: flex;justify-content: space-between;">
                <el-form :model="user" ref="form1" label-width="80px" class="form" label-position="left">
                    <el-form-item class="formitem">
                        <el-avatar
                            :src="user.avatar ? user.avatar : 'https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png'"
                            :size="130" style="margin-left: 30px;"></el-avatar>
                    </el-form-item>
                    <el-form-item label="用户名" class="formitem">
                        <div style="display: flex;align-items: center;">
                            <el-input :disabled="!nameedit" v-model="user.username" size="small"></el-input>
                            <el-button type="primary" size="mini" style="height: 15%;width: 18%;margin-left: 15px;"><i
                                    class="el-icon-edit" style="font-size: 16px;" @click="handlenameedit"></i></el-button>
                        </div>
                    </el-form-item>
                    <el-form-item label="用户邮箱" class="formitem">
                        <div style="display: flex;align-items: center;">
                            <el-input :disabled="!emailedit" v-model="user.email" size="mini"></el-input>
                            <el-button type="primary" size="mini" style="height: 15%;width: 18%;margin-left: 15px;"><i
                                    class="el-icon-edit" style="font-size: 16px;" @click="handleemailedit"></i></el-button>
                        </div>
                    </el-form-item>
                    <el-form-item label="用户身份" class="formitem">
                        <span>{{ user.identity === 0 ? '数据标注员' : (user.identity === 1 ? '项目管理员' : '平台管理员') }}</span>
                    </el-form-item>
                    <el-form-item label="用户公司" class="formitem">
                        <span>{{ user.company }}</span>
                    </el-form-item>
                    <el-form-item label="所属部门" class="formitem">
                        <span>{{ user.position }}</span>
                    </el-form-item>
                </el-form>
                <el-divider direction="vertical"></el-divider>
                <div style="display: flex;flex-direction: column;align-items: center;width: 850px;">
                    <span style="color: rgb(100,100,101);font-size: 25px;">消息盒子</span>
                    <el-divider></el-divider>
                    <div v-for="item in message.slice((currentPage - 1) * pageSize, pageSize * currentPage)" :key="item.time" style="width: 100%;">
                        <div style="display: flex;justify-content: space-between;width: 100%;font-size: 20px;cursor: pointer;">
                            <span>{{ item.content }}</span>
                            <span>{{ item.time }}</span>
                        </div>
                        <el-divider></el-divider>
                    </div>
                    <el-pagination  :current-page="currentPage"
                    :page-size="pageSize" background layout="sizes, prev, pager, next, jumper" :total="message.length"
                    @current-change="handleCurrentChange" />
                </div>
            </div>
        </el-card>
    </div>
</template>
<script>
export default {
    name: "PersonCenter",
    data() {
        return {
            currentPage: 1,
            pageSize:5,
            user: {
                email: "4892551682@qq.com",
                identity: 1,
                avatar: null,
                company: "鼠鼠有限公司",
                position: "觅食部门鼠威先锋",
                username: "鼠鼠"
            },
            nameedit: false,
            emailedit: false,
            message: [
                {
                    time: "2023-11-2fsd1 18:00:00",
                    content: "消息一",
                },
                {
                    time: "2023-11-21fds 18:00:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:rwe00:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18hgdf:00:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18ty:00:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:yr00:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:er00:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:00we:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:00ewdes:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:04560:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:00:54500",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:00rwerwer00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:00:erwhfg00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:0erwrewyt0:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:00ret:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:0tr0:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:jhg00:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:00ZXz:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:dasr00:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:hgd00:00",
                    content: "消息一"
                },
                {
                    time: "2023-11-21 18:0fg0:00",
                    content: "消息一"
                },
            ]
        }
    },
    methods: {
        goBack() {
            this.$router.back()
        },
        handleCurrentChange(val) {
            this.currentPage = val
        },
        handlenameedit() {
            if (this.user.username === "" && this.nameedit) {
                console.log(1);
                this.$message.error("用户名不能为空")
            } else {
                console.log(2);
                this.nameedit = !this.nameedit
            }
        },
        handleemailedit() {
            if (this.user.email === "" && this.emailedit) {
                this.$message.error("邮箱不能为空")
            } else {
                this.emailedit = !this.emailedit
            }
        }
    },
    mounted() {

    }
}
</script>
<style scoped>
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
/deep/.el-divider--vertical {
    display: inline-block;
    width: 1px;
    height: 31em;
    margin: 0 8px;
    vertical-align: middle;
    position: relative;
}
</style>