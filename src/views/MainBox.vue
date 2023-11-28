<template>
    <el-container>
        <el-header :class="{elHeader:$store.state.islight,elHeader2:!$store.state.islight}">
            <TopMenu></TopMenu>
        </el-header>
        <el-container>
            <el-aside :width="!$store.state.iscollapse?'10%':'4.2%'"><SideMenu/></el-aside>
            <el-main :key="$store.state.index" :class="{elMain1:$store.state.islight,elMain2:!$store.state.islight}"><router-view></router-view></el-main>
        </el-container>
    </el-container>
</template>
<script>
import TopMenu from '@/components/TopMenu.vue'
import SideMenu from '@/components/SideMenu.vue'
//import axios from 'axios'
export default {
    name:"MainBox",
    components: {
        TopMenu,
        SideMenu
    },
    data() {
        return {

        }
    },
    methods: {

    },
    mounted() {
        /*axios.get("https://items-storage.oss-cn-beijing.aliyuncs.com/UserAvatar/project.json",).then((res) => {
            console.log(res.data);
        })*/
    }
}
</script>
<style>
.el-container {
    width: 100%;
    height: 100%;
}
.elHeader {
    background-color: white;
    color: #333;
    text-align: center;
    line-height: 60px;
}

.el-aside {
    background-color: #D3DCE6;
    color: #333;
    text-align: center;
    line-height: 200px;
    padding: 0;
}
.elAside {
    background-color: #D3DCE6;
    color: #333;
    text-align: center;
    line-height: 200px;
    padding: 0;
}
.elMain1 {
    background-color: #E9EEF3;
    color: #333;
    padding:0px;
}
.elMain2 {
    background-color: rgb(70,78,97);
    color: #333;
    padding:0px;
}
body>.el-container {
    margin-bottom: 40px;
}

.el-container:nth-child(5) .el-aside,
.el-container:nth-child(6) .el-aside {
    line-height: 260px;
}

.el-container:nth-child(7) .el-aside {
    line-height: 320px;
}
</style>