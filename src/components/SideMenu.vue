<template>
    <el-aside width='100%'>
        <el-menu class="el-menu-vertical-demo" :class="{ elMenu: $store.state.islight, elMenu2: !$store.state.islight }"
            :collapse="$store.state.iscollapse" v-if="$store.state.user.identity === 1" router
            :collapse-transition="false" :default-active="'/' + $route.fullPath.split('/')[1]">
            <el-submenu :class="{ elSubmenuTitle: $store.state.islight, elSubmenuTitle2: !$store.state.islight }"
                index="project">
                <template slot="title">
                    <i class="el-icon-money-funds"></i>
                    <span slot="title">项目管理</span>
                </template>
                <el-menu-item :class="{ elMenuItem: $store.state.islight, elMenuItem2: !$store.state.islight }"
                    index="/CreateProject"><i class="el-icon-product"></i> 项目创建</el-menu-item>
                <el-menu-item :class="{ elMenuItem: $store.state.islight, elMenuItem2: !$store.state.islight }"
                    index="/ProjectList"><i class="el-icon-icon-test1"></i>项目列表</el-menu-item>
            </el-submenu>
            <el-submenu :class="{ elSubmenuTitle: $store.state.islight, elSubmenuTitle2: !$store.state.islight }"
                index="Task">
                <template slot="title">
                    <i class="el-icon-order-manage"></i>
                    <span slot="title">项目调度</span>
                </template>
                <el-menu-item :class="{ elMenuItem: $store.state.islight, elMenuItem2: !$store.state.islight }"
                    index="/TaskSchedule"><i class="el-icon-order"></i> 任务调度</el-menu-item>
                <el-menu-item :class="{ elMenuItem: $store.state.islight, elMenuItem2: !$store.state.islight }"
                    index="/TaskList"><i class="el-icon-list"></i> 任务列表</el-menu-item>
            </el-submenu>
            <el-submenu :class="{ elSubmenuTitle: $store.state.islight, elSubmenuTitle2: !$store.state.islight }"
                index="Mark">
                <template slot="title">
                    <i class="el-icon-edit"></i>
                    <span slot="title">在线标注</span>
                </template>
                <el-menu-item :class="{ elMenuItem: $store.state.islight, elMenuItem2: !$store.state.islight }"
                    index="/LabelManager"><i class="el-icon-a-business-icon-Bigpromotion"></i> 标签组管理</el-menu-item>
                <el-menu-item :class="{ elMenuItem: $store.state.islight, elMenuItem2: !$store.state.islight }"
                    index="/MakeMark"><i class="el-icon-icon-test"></i> 任务标注</el-menu-item>
            </el-submenu>
            <!-- <el-menu-item :class="{ elMenuItem: $store.state.islight, elMenuItem2: !$store.state.islight }"
                index="/DataReview">
                <i class="el-icon-product-checked"></i>
                <span slot="title">数据审核</span>
            </el-menu-item> -->
            <el-menu-item :class="{ elMenuItem: $store.state.islight, elMenuItem2: !$store.state.islight }"
                index="/DataPublish">
                <i class="el-icon-training-fill"></i>
                <span slot="title">数据发布</span>
            </el-menu-item>
            <el-menu-item :class="{ elMenuItem: $store.state.islight, elMenuItem2: !$store.state.islight }"
                index="/ProjectAnaysis">
                <i class="el-icon-editor-four-column"></i>
                <span slot="title">项目分析</span>
            </el-menu-item>
        </el-menu>
        <el-menu class="el-menu-vertical-demo" :class="{ elMenu: $store.state.islight, elMenu2: !$store.state.islight }"
            :collapse="$store.state.iscollapse" v-if="$store.state.user.identity === 2" router
            :collapse-transition="false">
            <el-submenu index="project">
                <template slot="title">
                    <i class="el-icon-money-funds"></i>
                    <span slot="title">项目管理</span>
                </template>
                <el-menu-item index="/ProjectList"><i class="el-icon-icon-test1"></i>项目列表</el-menu-item>
                <el-menu-item index="/ProjectSchedule"><i class="el-icon-refresh"></i>项目调度</el-menu-item>
                <el-menu-item index="/CreateProject"><i class="el-icon-product"></i>新增项目</el-menu-item>
            </el-submenu>
            <el-submenu index="user">
                <template slot="title">
                    <i class="el-icon-user"></i>
                    <span slot="title">员工管理</span>
                </template>
                <el-menu-item index="/AddUser"><i class="el-icon-folder-add"></i>员工导入</el-menu-item>
                <el-menu-item index="/UserList"><i class="el-icon-user-solid"></i>员工列表</el-menu-item>
                <el-menu-item index="/UserSchedule"><i class="el-icon-bell"></i>员工调度</el-menu-item>
            </el-submenu>
            <el-submenu index="Permission">
                <template slot="title">
                    <i class="el-icon-s-check"></i>
                    <span slot="title">权限管理</span>
                </template>
                <el-menu-item index="/PermissionReview"><i class="el-icon-coordinate"></i>权限审核</el-menu-item>
                <el-menu-item index="/PermissionChange"><i class="el-icon-collection"></i>权限修改</el-menu-item>
            </el-submenu>
            <el-menu-item index="/PlatformRegulation">
                <i class="el-icon-takeaway-box"></i>
                <span slot="title">平台规范</span>
            </el-menu-item>
            <el-menu-item index="/TaskAnaysis">
                <i class="el-icon-tickets"></i>
                <span slot="title">业务分析</span>
            </el-menu-item>
        </el-menu>
        <el-menu class="el-menu-vertical-demo" :class="{ elMenu: $store.state.islight, elMenu2: !$store.state.islight }"
            :collapse="$store.state.iscollapse" :collapse-transition="false" v-if="$store.state.user.identity === 0"
            router :default-active="'/' + $route.fullPath.split('/')[1]">
            <el-menu-item index="/MakeMark"><i class="el-icon-icon-test"></i><span
                    slot="title">任务标注</span></el-menu-item>
            <el-menu-item index="/PermissionReuest"><i class="el-icon-printer"></i><span
                    slot="title">权限申请</span></el-menu-item>
        </el-menu>
        <el-menu class="el-menu-vertical-demo" :class="{ elMenu: $store.state.islight, elMenu2: !$store.state.islight }"
            :collapse="$store.state.iscollapse" :collapse-transition="false" v-if="$store.state.user.identity === 3"
            router :default-active="'/' + $route.fullPath.split('/')[1]">
            <el-menu-item index="/CheckMaterial"><i class="el-icon-icon-test"></i><span
                    slot="title">入驻审核</span></el-menu-item>
            <el-menu-item index="/CompanyManagement"><i class="el-icon-printer"></i><span
                    slot="title">入驻管理</span></el-menu-item>
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

.elMenu {
    background-color: #D3DCE6;
    color: #333;
}

.elMenu2 {
    background-color: rgb(36, 46, 62);
    color: white;
}

.el-menu-vertical-demo:not(.el-menu--collapse) {
    width: 100%;
    height: 100%;
    padding: 0;
}

.elMenuItem {
    color: #303133;
    transition: border-color .3s, background-color .3s, color .3s;
    box-sizing: border-box;
    white-space: nowrap;
}

.elMenuItem2 {
    color: rgb(100, 100, 101);
    transition: border-color .3s, background-color .3s, color .3s;
    box-sizing: border-box;
    white-space: nowrap;
}

.el-menu-vertical-demo {
    width: 100%;
    height: 100%;
    padding: 0;
}

.elSubmenuTitle {
    font-size: 14px;
    color: #303133;
    padding: 0 0px;
    cursor: pointer;
    transition: border-color .3s, background-color .3s, color .3s;
    box-sizing: border-box;
}

.elSubmenuTitle2 {
    font-size: 14px;
    color: rgb(100, 100, 101);
    padding: 0 0px;
    cursor: pointer;
    transition: border-color .3s, background-color .3s, color .3s;
    box-sizing: border-box;
}
</style>