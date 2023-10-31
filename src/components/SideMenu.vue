<template>
    <el-aside width='100%'>
        <el-menu  
            class="el-menu-vertical-demo"
            :collapse="$store.state.iscollapse" 
            v-if="$store.state.user.identity === 1" 
            router 
            :collapse-transition="false"
            :default-active="$route.fullPath">
            <el-submenu index="project">
                <template slot="title">
                    <i class="el-icon-location"></i>
                    <span slot="title">项目管理</span>
                </template>
                <el-menu-item index="/CreateProject">项目创建</el-menu-item>
                <el-menu-item index="/ProjectList">项目列表</el-menu-item>
            </el-submenu>
            <el-submenu index="Task">
                <template slot="title">
                    <i class="el-icon-location"></i>
                    <span slot="title">项目调度</span>
                </template>
                <el-menu-item index="/TaskSchedule">任务调度</el-menu-item>
                <el-menu-item index="/TaskList">任务列表</el-menu-item>
            </el-submenu>
            <el-submenu index="Mark">
                <template slot="title">
                    <i class="el-icon-location"></i>
                    <span slot="title">在线标注</span>
                </template>
                <el-menu-item index="/LabelManager">标签组管理</el-menu-item>
                <el-menu-item index="/MakeMark">任务标注</el-menu-item>
            </el-submenu>
            <el-menu-item index="/DataReview">
                <i class="el-icon-menu"></i>
                <span slot="title">数据审核</span>
            </el-menu-item>
            <el-menu-item index="/DataPublish">
                <i class="el-icon-menu"></i>
                <span slot="title">数据发布</span>
            </el-menu-item>
            <el-menu-item index="/ProjectAnaysis">
                <i class="el-icon-menu"></i>
                <span slot="title">项目分析</span>
            </el-menu-item>
        </el-menu>
        <el-menu  class="el-menu-vertical-demo"
            :collapse="$store.state.iscollapse"  v-if="$store.state.user.identity === 2" router :collapse-transition="false">
            <el-submenu index="project">
                <template slot="title">
                    <i class="el-icon-location"></i>
                    <span slot="title">项目管理</span>
                </template>
                <el-menu-item index="/ProjectList">项目列表</el-menu-item>
                <el-menu-item index="/ProjectSchedule">项目调度</el-menu-item>
                <el-menu-item index="/CreateProject">新增项目</el-menu-item>
            </el-submenu>
            <el-submenu index="user">
                <template slot="title">
                    <i class="el-icon-location"></i>
                    <span slot="title">用户管理</span>
                </template>
                <el-menu-item index="/UserList">用户列表</el-menu-item>
                <el-menu-item index="/UserSchedule">用户调度</el-menu-item>
            </el-submenu>
            <el-submenu index="Permission">
                <template slot="title">
                    <i class="el-icon-location"></i>
                    <span slot="title">权限管理</span>
                </template>
                <el-menu-item index="/PermissionReview">权限审核</el-menu-item>
                <el-menu-item index="/PermissionChange">权限修改</el-menu-item>
            </el-submenu>
            <el-menu-item index="/PlatformRegulation">
                <i class="el-icon-menu"></i>
                <span slot="title">平台规范</span>
            </el-menu-item>
            <el-menu-item index="/TaskAnaysis">
                <i class="el-icon-menu"></i>
                <span slot="title">业务分析</span>
            </el-menu-item>
        </el-menu>
        <el-menu  class="el-menu-vertical-demo"
            :collapse="$store.state.iscollapse" :collapse-transition="false" v-if="$store.state.user.identity === 0" router>
            <el-submenu index="Mark">
                <template slot="title">
                    <i class="el-icon-location"></i>
                    <span slot="title">在线标注</span>
                </template>
                <el-menu-item index="/MarkList">任务列表</el-menu-item>
                <el-menu-item index="/MakeMark">任务标注</el-menu-item>
            </el-submenu>
            <el-menu-item index="/PermissionReuest">权限申请</el-menu-item>
        </el-menu>
    </el-aside>
</template>
<script>
export default {
    name: "SideMenu",
    data() {
        return {

        }
    },
    methods: {

    },
    mounted() {
    }
}
</script>
<style>
.el-aside {
    background-color: #D3DCE6;
    color: #333;
    text-align: center;
    padding: 0px;
    height: 100%;
    overflow-x: hidden;
}

.el-menu-vertical-demo:not(.el-menu--collapse) {
    width: 100%;
    height: 100%;
    padding: 0;
}

.el-menu-vertical-demo {
    width: 100%;
    height: 100%;
    padding: 0;
}
</style>