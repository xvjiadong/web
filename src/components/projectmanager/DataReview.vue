<template>
    <div class="container">
        <div class="header">
            <span style="font-size: 16px;color: rgb(21,27,38);">数据审核</span>
            <div style="display: flex;justify-content: space-between;">
                <span
                    style="font-size: 10px;color: rgb(21,27,38);">标注审核是指对标注结果进行审核和修正的过程，其目的是确保标注结果的准确性和一致性。</span>
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
                        恒生电子数据标注平台为一站式数据处理和服务平台，在数据审核模式下项目管理员对已完成的任务进行审核
                    </span>
                </div>
            </div>
            <div class="teachbody">
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/任务1.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            选择待审核任务
                        </div>
                        <div class="itemcontent">
                            当分派任务的所有子任务被完成后，可以选择该任务进行审核
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/任务2.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            数据审核
                        </div>
                        <div class="itemcontent">
                            标注审核的流程包括对标注结果进行初步审核、对标注错误进行修正、对标注结果进行二次审核、对标注结果进行统计和分析等步骤。
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/任务3.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            任务归纳
                        </div>
                        <div class="itemcontent">
                            归纳任务数据：符合规范，则将其纳入到版本数据集中；如果不符合规范，将不符合规范的数据重新形成一个新的任务，重新指派数据标注员进行标注
                        </div>
                    </div>
                </div>
            </div>
        </el-card>
        <el-card class="teachcard">
            <div slot="header" style="display: flex;justify-content: space-between;align-items:center">
                <el-menu :default-active="'create'" mode="horizontal">
                    <el-menu-item index="create">待审核的任务</el-menu-item>
                </el-menu>
            </div>
            <div>
                <el-table :data="createtask" :row-key="getrowkey" :key="update">
                    <el-table-column type="expand" width="75" label="子任务">
                        <template slot-scope="scope">
                            <div style="text-align:center">
                                <el-table :data="scope.row.taskUser" :row-key="getrowkey">
                                    <el-table-column prop="userId" width="105" label="任务承办人"></el-table-column>
                                    <el-table-column prop="dataNumber" label="标注数量"></el-table-column>
                                    <el-table-column prop="personalProgress" label="审核进度"></el-table-column>
                                    <el-table-column label="操作">
                                        <template slot-scope="scope2">
                                            <el-button size="mini"
                                                @click="push(scope.row, scope2.row)">审核</el-button>
                                            <el-button size="mini"
                                                @click="handleremove(scope.row, scope2.row)">移交</el-button>
                                        </template>
                                    </el-table-column>
                                </el-table>
                            </div>
                        </template>
                    </el-table-column>
                    <el-table-column width="80" prop="taskName" label="任务名"></el-table-column>
                    <el-table-column width="150" prop="projectName" label="所属项目"></el-table-column>
                    <el-table-column width="150" prop="version" label="所属版本"></el-table-column>
                    <el-table-column width="150" prop="callType" label="任务类型"></el-table-column>
                    <el-table-column width="150" prop="progress" label="审核总进度"></el-table-column>
                    <el-table-column width="180" prop="startTime" label="创建时间"></el-table-column>
                    <el-table-column width="180" prop="endTime" label="截止时间"></el-table-column>
                    <el-table-column label="操作">
                        <template slot-scope="scope">
                            <span size="mini" class="tableplay" @click="push(scope.row)">审核</span>
                            <span size="mini" class="tableplay" @click="handleDelete(scope.row)">删除</span>
                        </template>
                    </el-table-column>
                </el-table>
            </div>
        </el-card>
    </div>
</template>
<script>
export default {
    name: "DataReview",
    components: {

    },
    data() {
        return {
            hideintroduction: false,
            createtask: [
                {
                    taskName: "45845",
                    callType: "图像文本标注",
                    version: "v1",
                    id: "4965",
                    projectName: "4445",
                    progress: "15%",
                    startTime: "2023-11-07 18:23",
                    endTime: "2023-11-17 18:23",
                    taskUser: [
                        {
                            userId: 1,
                            dataNumber: "159",
                            personalProgress: "15%"
                        },
                        {
                            userId: 2,
                            dataNumber: "159",
                            personalProgress: "15%"
                        },
                        {
                            userId: 3,
                            dataNumber: "159",
                            personalProgress: "15%"
                        },
                    ]
                },
                {
                    taskName: "4596",
                    callType: "信息抽取标注",
                    version: "v1",
                    id: "49654845",
                    projectName: "4445",
                    progress: "15%",
                    startTime: "2023-11-07 18:23",
                    endTime: "2023-11-17 18:23",
                    taskUser: [
                        {
                            userId: 4,
                            dataNumber: "159",
                            personalProgress: "15%"
                        },
                        {
                            userId: 5,
                            dataNumber: "159",
                            personalProgress: "15%"
                        },
                        {
                            userId: 6,
                            dataNumber: "159",
                            personalProgress: "15%"
                        },
                    ]
                },
                {
                    taskName: "45",
                    callType: "文本分类标注",
                    version: "v1",
                    id: "496uiu5",
                    projectName: "4445",
                    progress: "15%",
                    startTime: "2023-11-07 18:23",
                    endTime: "2023-11-17 18:23",
                    taskUser: [
                        {
                            userId: 7,
                            dataNumber: "159",
                            personalProgress: "15%"
                        },
                        {
                            userId: 8,
                            dataNumber: "159",
                            personalProgress: "15%"
                        },
                        {
                            userId: 9,
                            dataNumber: "159",
                            personalProgress: "15%"
                        },
                    ]
                },
                {
                    taskName: "484535",
                    callType: "图片分类标注",
                    version: "v1",
                    id: "496iuiu7t5",
                    projectName: "4445",
                    progress: "15%",
                    startTime: "2023-11-07 18:23",
                    endTime: "2023-11-17 18:23",
                    taskUser: [
                        {
                            userId: 10,
                            dataNumber: "159",
                            personalProgress: "15%"
                        },
                        {
                            userId: 11,
                            dataNumber: "159",
                            personalProgress: "15%"
                        },
                        {
                            userId: 12,
                            dataNumber: "159",
                            personalProgress: "15%"
                        },
                    ]
                },
            ],
            update:false
        }
    },
    computed: {

    },
    methods: {
        push(row,child=null) {
            let router
            if (row.callType === "图像文本标注") {
                router="/"+"PicReview"
            } else if (row.callType === "信息抽取标注") {
                router="/"+"PdfReview"
            } else if (row.callType === "图片分类标注") {
                router="/"+"PicPartReview"
            } else if (row.callType === "文本分类标注") {
                router="/"+"TextPartReview"
            }
            this.$router.push({
                path: router,
                query: {
                    projectid: row.id,
                    version: row.version,
                    marktype: row.callType,
                    projectname: row.projectName,
                    userId: (typeof child ==="number")?child.userId:null
                }
            })
        },
        hide() {
            this.hideintroduction = !this.hideintroduction
        },
        getrowkey(row) {
            return row.userId ||row.taskName
        },
        a(scope) {
            console.log(scope);
        },
        handleTaskLook(item1) {
            console.log(item1);
        },
        handleTaskLookpart(item1, item2) {
            console.log(item1, item2);
        },
        handleremove(item1, item2) {
            console.log(item1, item2);
        },
        handleDelete(item) {
            console.log(item);
        },
    },
    mounted() {
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