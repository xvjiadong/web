<template>
    <div class="container">
        <div class="header">
            <span style="font-size: 16px;color: rgb(21,27,38);">任务列表</span>
            <div style="display: flex;justify-content: space-between;">
                <span
                    style="font-size: 10px;color: rgb(21,27,38);">多人协同任务标注功能可通过团队协作方式，提高数据标注效率。任务发起后，系统会向团队成员自动分发标注任务，成员完成标注提交任务后，任务发起人可以进行标注结果验收。</span>
                <span class="hide" @click="hide">
                    {{ hideintroduction ? "展开" : "隐藏" }}使用介绍
                </span>
            </div>
        </div>
        <el-card class="teachcard" v-if="!hideintroduction">
            <div slot="header">
                <span style="font-size: 16px;color: rgb(21,27,38);">
                    使用流程
                </span>
                <br>
                <div>
                    <span style="font-size: 10px;color: #84868c;">
                        恒生电子数据标注平台为一站式数据处理和服务平台，在多人协同标注模式下以任务为基本单元进行标注工作
                    </span>
                </div>
            </div>
            <div class="teachbody">
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/任务1.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            选择数据集版本
                        </div>
                        <div class="itemcontent">
                            您只可选择由您创建的、此时未被标注的数据集版本，并提前设定数据集版本的标注标签，任务过程中标注标签不支持增删改查
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/任务2.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            选择标注团队
                        </div>
                        <div class="itemcontent">
                            您可以通过添加团队成员的方式自定义标注团队成员，一个标注团队成员上限10人，支持任务过程中修改团队成员
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/任务3.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            标注任务分发
                        </div>
                        <div class="itemcontent">
                            选定标注团队后系统将根据任务总数随机分配个人任务，并将任务通知发送到团队成员邮箱，支持标注过程中调度任务
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/pickind.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            数据标注
                        </div>
                        <div class="itemcontent">
                            选择任务后进入标注界面进行数据标注任务，主要为信息抽取标注、文本分类标注、图像文本标注、图片分类标注四大类型
                        </div>
                    </div>
                </div>
            </div>
        </el-card>
        <el-card class="teachcard">
            <div slot="header" style="display: flex;justify-content: space-between;align-items:center">
                <el-menu :default-active="'create'" mode="horizontal">
                    <el-menu-item index="create" @click="mode = 0">创建的任务</el-menu-item>
                    <el-menu-item index="accpet" @click="mode = 1">接受的任务</el-menu-item>
                </el-menu>
                <el-button type="primary" size="mini" style="background-color: rgb(36,104,242);margin-right: 20px">
                    <i class="el-icon-plus"></i>&emsp;项目团队管理
                </el-button>
            </div>
            <div v-if="mode === 0">
                <el-table :data="createtask" :row-key="getrowkey" :key="update">
                    <el-table-column type="expand" width="75" label="子任务">
                        <template slot-scope="scope">
                            <div style="text-align:center" v-if="scope.row.taskUser">
                                <el-table :data="scope.row.taskUser" :row-key="getrowkey">
                                    <el-table-column prop="userId" width="105" label="任务承办人"></el-table-column>
                                    <el-table-column prop="dataNumber" label="标注数量"></el-table-column>
                                    <el-table-column prop="personalProgress" label="子任务进度"></el-table-column>
                                    <el-table-column label="操作">
                                        <template slot-scope="scope2">
                                            <el-button size="mini"
                                                @click="handleTaskLook(scope.row, scope2.row)">查看</el-button>
                                            <el-button size="mini"
                                                @click="handleremove(scope.row, scope2.row)">移交</el-button>
                                        </template>
                                    </el-table-column>
                                </el-table>
                            </div>
                            <div style="text-align:center; " v-else>
                                <el-empty description="未分配任务" style="padding:0px;color:rgb(21,27,38)">
                                    <span slot @click="handleSchedule(item, scope.row)"
                                        style="color:rgb(36,104,242);cursor: pointer;">
                                        去分配任务
                                    </span>
                                </el-empty>
                            </div>
                        </template>
                    </el-table-column>
                    <el-table-column width="80" prop="taskName" label="任务名"></el-table-column>
                    <el-table-column width="80" prop="projectName" label="所属项目"></el-table-column>
                    <el-table-column width="80" prop="version" label="所属版本"></el-table-column>
                    <el-table-column width="120" prop="callType" label="任务类型"></el-table-column>
                    <el-table-column width="120" prop="progress" label="任务进度"></el-table-column>
                    <el-table-column width="150" prop="startTime" label="创建时间"></el-table-column>
                    <el-table-column width="150" prop="endTime" label="截止时间"></el-table-column>
                    <el-table-column label="操作">
                        <template slot-scope="scope">
                            <span size="mini" class="tableplay" @click="handleTaskLook(scope.row)">任务详情</span>
                            <span size="mini" class="tableplay" @click="handleTaskLook(scope.row)">查看进度</span>
                            <span size="mini" class="tableplay" @click="handleTaskLook(scope.row)">任务转让</span>
                            <span size="mini" class="tableplay" @click="handletask(scope.row)">删除</span>
                        </template>
                    </el-table-column>
                </el-table>

            </div>
            <div v-if="mode === 1">
                <el-table ref="accept" :data="accepttask">
                    <el-table-column type="expand" width="0"></el-table-column>
                    <el-table-column width="80" prop="projectid" label="所属项目"></el-table-column>
                    <el-table-column width="80" prop="projectversion" label="所属版本"></el-table-column>
                    <el-table-column width="150" prop="taskcreator" label="任务创建者"></el-table-column>
                    <el-table-column width="150" prop="tasknumber" label="数据量"></el-table-column>
                    <el-table-column width="150" prop="taskprocess" label="标注进度"></el-table-column>
                    <el-table-column width="150" prop="marktype" label="标注类型"></el-table-column>
                    <el-table-column width="150" prop="createtime" label="创建时间"></el-table-column>
                    <el-table-column width="150" prop="deadlinetime" label="截止时间"></el-table-column>
                    <el-table-column label="操作">
                        <template slot-scope="scope">
                            <span size="mini" class="tableplay" @click="handlemark(scope.row)"
                                v-if="scope.row.taskprocess !== '100%'">标注</span>
                            <span size="mini" class="tableplay" @click="handlereview(scope.row)"
                                v-if="scope.row.taskprocess === '100%'">审核</span>
                            <span size="mini" class="tableplay" @click="handletaskturn(scope.row)">转让</span>
                        </template>
                    </el-table-column>
                </el-table>
            </div>
        </el-card>
    </div>
</template>
<script>
import Task from "../../../public/task.json"
export default {
    name: "TaskList",
    components: {

    },
    data() {
        return {
            hideintroduction: false,
            createtask: [
                {
                    taskname: "45845",
                    tasktype: "图像文本标注",
                    taskbelongversion: "v1",
                    taskbelongprojectid: "4965",
                    taskbelongprojectname: "4445",
                    taskprocess: "15%",
                    createtime: "2023-11-07 18:23",
                    deadlinetime: "2023-11-17 18:23",
                    childrentask: [
                        {
                            taskperson: "小五",
                            tasknumber: "159",
                            taskprocess: "15%"
                        },
                        {
                            taskperson: "小六",
                            tasknumber: "159",
                            taskprocess: "15%"
                        },
                        {
                            taskperson: "小七",
                            tasknumber: "159",
                            taskprocess: "15%"
                        },
                    ]
                },
                {
                    taskname: "4596",
                    tasktype: "信息抽取标注",
                    taskbelongversion: "v1",
                    taskbelongprojectid: "49654845",
                    taskbelongprojectname: "4445",
                    taskprocess: "15%",
                    createtime: "2023-11-07 18:23",
                    deadlinetime: "2023-11-17 18:23",
                    childrentask: [
                        {
                            taskperson: "小五",
                            tasknumber: "159",
                            taskprocess: "15%"
                        },
                        {
                            taskperson: "小六",
                            tasknumber: "159",
                            taskprocess: "15%"
                        },
                        {
                            taskperson: "小七",
                            tasknumber: "159",
                            taskprocess: "15%"
                        },
                    ]
                },
                {
                    taskname: "45",
                    tasktype: "文本分类标注",
                    taskbelongversion: "v1",
                    taskbelongprojectid: "496uiu5",
                    taskbelongprojectname: "4445",
                    taskprocess: "15%",
                    createtime: "2023-11-07 18:23",
                    deadlinetime: "2023-11-17 18:23",
                    childrentask: [
                        {
                            taskperson: "小五",
                            tasknumber: "159",
                            taskprocess: "15%"
                        },
                        {
                            taskperson: "小六",
                            tasknumber: "159",
                            taskprocess: "15%"
                        },
                        {
                            taskperson: "小七",
                            tasknumber: "159",
                            taskprocess: "15%"
                        },
                    ]
                },
                {
                    taskname: "484535",
                    tasktype: "图片分类标注",
                    taskbelongversion: "v1",
                    taskbelongprojectid: "496iuiu7t5",
                    taskbelongprojectname: "4445",
                    taskprocess: "15%",
                    createtime: "2023-11-07 18:23",
                    deadlinetime: "2023-11-17 18:23",
                    childrentask: [
                        {
                            taskperson: "小五",
                            tasknumber: "159",
                            taskprocess: "15%"
                        },
                        {
                            taskperson: "小六",
                            tasknumber: "159",
                            taskprocess: "15%"
                        },
                        {
                            taskperson: "小七",
                            tasknumber: "159",
                            taskprocess: "15%"
                        },
                    ]
                },
            ],
            accepttask: [
                {
                    projectid: "4855657",
                    projectversion: "v1",
                    taskcreator: "484554",
                    tasknumber: 159,
                    taskprocess: "15%",
                    createtime: "2023-11-07 18:23",
                    deadlinetime: "2023-11-17 18:23",
                    marktype: "图像文本标注"
                },
                {
                    projectid: "48was557",
                    projectversion: "v1",
                    taskcreator: "484554",
                    tasknumber: 159,
                    taskprocess: "15%",
                    createtime: "2023-11-07 18:23",
                    deadlinetime: "2023-11-17 18:23",
                    marktype: "信息抽取标注"
                },
                {
                    projectid: "48lkj557",
                    projectversion: "v1",
                    taskcreator: "484554",
                    tasknumber: 159,
                    taskprocess: "15%",
                    createtime: "2023-11-07 18:23",
                    deadlinetime: "2023-11-17 18:23",
                    marktype: "图片分类标注"
                },
                {
                    projectid: "485fxd57",
                    projectversion: "v1",
                    taskcreator: "484554",
                    tasknumber: 159,
                    taskprocess: "15%",
                    createtime: "2023-11-07 18:23",
                    deadlinetime: "2023-11-17 18:23",
                    marktype: "文本分类标注"
                },
            ],
            mode: 0,
            update:false
        }
    },
    computed: {

    },
    methods: {
        hide() {
            this.hideintroduction = !this.hideintroduction
        },
        getrowkey(row) {
            return row.userId ||row.taskName
        },
        a(scope) {
            console.log(scope);
        },
        handleTaskLook(item1, item2) {
            console.log(item1, item2);
        },
        handleremove(item1, item2) {
            console.log(item1, item2);
        },
        handlemark(item) {
            console.log(item);
        },
        handlereview(item) {
            console.log(item);
        },
        handletaskturn(item) {
            console.log(item);
        }
    },
    mounted() {
        this.createtask = Task.data
        this.update=!this.update
    },
}
</script>
<style scoped>
.container {
    width: 100%;
    height: 643px;
}

.header {
    width: 97.4%;
    padding: 10px;
    margin: 10px;
    height: 8%;
    background-color: white;
    display: flex;
    flex-direction: column;
    justify-content: space-between;
    align-items: left;
    text-align: left;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
}

.teachcard {
    text-align: left;
    margin: 10px;
}

.teachbody {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: space-around;
}

.teachbodyitem {
    display: flex;
    flex-direction: row;
    align-items: center;
    flex-direction: column;
    justify-content: center;
}

.itemtitle {
    font-size: var(--fontSize, 14px);
    color: var(--colorGray10, #151b26);
    line-height: 22px;
    margin: 10px 0 8px;
    text-align: center;
}

.itemcontent {
    font-size: var(--smFontSize, 12px);
    color: var(--colorGray7, #84868c);
    line-height: 20px;
    margin-bottom: 8px;
    width: 230px;
    overflow: hidden;
    text-overflow: ellipsis;
    display: -webkit-box;
    -webkit-line-clamp: 3;
    -webkit-box-orient: vertical;
    text-align: left;
}

.hide {
    font-size: 10px;
    color: #84868c;
    cursor: pointer;
}

.hide:hover {
    color: blue;
}

.box-card {
    width: 100%;
    height: 598px;
    margin-left: 1%;
}

.teachcard {
    text-align: left;
    margin: 10px;
}

/deep/.el-card__header {
    padding: 8px;
    padding-bottom: 0px;
}

.el-menu-item {
    padding: 0px;
    margin-left: 30px;
    font-size: 16px;
}

.el-menu--horizontal>.el-menu-item.is-active {
    border-bottom: 2px solid #409EFF;
    color: rgb(36, 104, 242);
}

/deep/.el-card__body {
    padding: 15px;
}

.listheaderitem {
    font-size: 14px;
    cursor: pointer;
    margin-right: 22px;
    color: #000;
    text-decoration: none;
    display: inline-flex;
    align-items: center;
}

.projectlist {
    margin-top: 15px
}

/deep/.el-table .el-table__cell {
    padding: 12px 0;
    min-width: 0;
    box-sizing: border-box;
    text-overflow: ellipsis;
    vertical-align: middle;
    position: relative;
    text-align: center;
}

.tableplay {
    margin-left: 8px;
    color: rgb(26, 115, 232);
    font-size: 12px;
    cursor: pointer;
}

.tableplay:hover {
    color: rgb(82, 142, 255);
}
</style>