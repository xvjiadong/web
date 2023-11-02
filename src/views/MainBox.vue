<template>
    <el-container>
        <el-header>
            <TopMenu></TopMenu>
        </el-header>
        <el-container>
            <el-aside :width="!$store.state.iscollapse?'10%':'4.2%'"><SideMenu/></el-aside>
            <el-main><router-view></router-view></el-main>
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
        /*axios.post("http://localhost:3000/try", { yet: 1 }).then((res) => {
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
.el-header {
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

.el-main {
    background-color: #E9EEF3;
    color: #333;
    text-align: center;
    line-height: 160px;
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