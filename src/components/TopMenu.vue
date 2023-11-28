<template>
    <el-header :class="{elHeader:$store.state.islight,elHeader2:!$store.state.islight}">
        <div class="left">
            <div :class='{menuiconnotcollapse:!$store.state.iscollapse,menuiconcollapse:$store.state.iscollapse}' @click="changemenu">
                <i class="el-icon-d-arrow-left" v-if="!$store.state.iscollapse" style="font-size: 3.5vh;"></i>
                <i class="el-icon-category" v-if="$store.state.iscollapse" style="font-size: 3.5vh;"></i>
                <span style="font-size: 100%;">{{ $store.state.iscollapse ? "" : "数据标注平台" }} </span>
            </div>
            <div class="model">
                <div style="height: 50%;display: flex;justify-content: center;align-items: center;">
                    {{ islight ? "高亮模式" : "护眼模式" }}
                </div>
                <el-switch v-model="islight" active-icon-class="el-icon-sunrise"
                    inactive-icon-class="el-icon-s-opportunity" @change="light"></el-switch>
            </div>
        </div>
        <div class="right">
            <ul class="rightmenu">
                <li>
                    <el-avatar :size="30" :src="avatar"></el-avatar>
                </li>
                <li>
                    <span>{{ $store.state.user.username }}</span>
                </li>
                <li>
                    <el-dropdown>
                        <span class="el-dropdown-link" :class="{text1:$store.state.islight,text2:!$store.state.islight}">
                            文档<i class="el-icon-arrow-down el-icon--right"></i>
                        </span>
                        <el-dropdown-menu slot="dropdown">
                            <el-dropdown-item>平台文档</el-dropdown-item>
                            <el-dropdown-item>视频教程</el-dropdown-item>
                        </el-dropdown-menu>
                    </el-dropdown>
                </li>
                <li @click="$router.push('/PersonCenter')">
                    个人
                </li>
                <li @click="exit">
                    退出
                </li>

            </ul>
        </div>
    </el-header>
</template>
<script>
export default {
    name: "TopMenu",
    data() {
        return {
            islight: this.$store.state.islight,
        }
    },
    computed: {
        avatar() {
            return this.$store.state.user.avatar ? this.$store.state.user.avatar : 'https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png'
        }
    },
    methods: {
        changemenu() {
            this.$store.commit("changeiscollapse")
        },
        exit() {
            localStorage.removeItem("token")
            this.$store.commit("clearuser")
            this.$router.push("/")
        },
        light(value) {
            console.log(value);
            this.$store.commit("changeislight",value)
        }
    },
    mounted() {

    }
}
</script>
<style>
.el-header {
    background-color: white;
    color: white;
    width: 100%;
    line-height: 60px;
    padding: 0;
    height: 60px;
    display: flex;
    justify-content: space-between;
    align-items: center;
}
.elHeader2 {
    background-color: rgb(39,46,62);
    color: white;
    width: 100%;
    line-height: 60px;
    padding: 0;
    height: 60px;
    display: flex;
    justify-content: space-between;
    align-items: center;
}
.menuiconnotcollapse {
    height: 100%;
    width: 20%;
    color: white;
    background-color: rgb(36, 104, 242);
    cursor: pointer;
    display: flex;
    align-items: center;
}
.menuiconcollapse {
    height: 100%;
    width: 8.4%;
    color: white;
    background-color: rgb(36, 104, 242);
    cursor: pointer;
    display: flex;
    justify-content: center;
    align-items: center;
}
.menuicon:hover {
    background-color: rgb(3, 50, 143);
}

.left {
    display: flex;
    justify-content: left;
    align-items: center;
    width: 50%;
    height: 100%;
}

.right {
    height: 100%;
    width: 50%;
}

.model {
    height: 100%;
    font-size: 11px;
    display: flex;
    flex-direction: column;
}

.rightmenu {
    list-style: none;
    display: flex;
    justify-content: right;
    height: 100%;
    margin: 0;
}

.rightmenu li {
    width: 10%;
    height: 100%;
    font-size: 12px;
    display: flex;
    align-items: center;
    justify-content: center;
}

.rightmenu li:hover {
    text-decoration: underline;
    color: rgb(36, 104, 242);
    cursor: pointer;
}
.text1{
    font-size: 12px;
}
.text2{
    font-size: 12px;
    color: white;
}
</style>