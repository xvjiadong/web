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
                    <el-table-column width="200" prop="taskName" label="任务名"></el-table-column>
                    <el-table-column width="80" prop="projectName" label="所属项目"></el-table-column>
                    <el-table-column width="80" prop="version" label="所属版本"></el-table-column>
                    <el-table-column width="150" prop="callType" label="任务类型"></el-table-column>
                    <el-table-column width="150" prop="progress" label="任务进度"></el-table-column>
                    <el-table-column width="150" prop="startTime" label="创建时间"></el-table-column>
                    <el-table-column width="150" prop="endTime" label="截止时间"></el-table-column>
                    <el-table-column label="操作">
                        <template slot-scope="scope">
                            <div v-if="scope.row.taskUser.length > 0">
                                <span size="mini" class="tableplay" @click="handleTaskLook(scope.row)">任务详情</span>
                                <span size="mini" class="tableplay" @click="handleTasklabel(scope.row)">查看标签</span>
                                <span size="mini" class="tableplay" @click="handleTaskLook(scope.row)">任务转让</span>
                            </div>
                            <div v-else>
                                <span size="mini" class="tableplay" @click="handleSchedule(scope.row)">任务调度</span>
                            </div>
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
        <el-dialog title="更新标签组" :visible.sync="labelvisible" width="24%" top="15%" :destroy-on-close="true"
            :show-close="false" :close-on-click-modal="false">
            <div style="height: 160px;overflow-y: auto;">
                <div style="display: flex;justify-content: left;">
                    <span>序号</span>
                    <span style="margin-left: 15px;">标签名</span>
                </div>
                <div v-for="(item, index) in show.labels" :key="index"
                    style="display: flex;justify-content: left;align-items: center;margin-top: 12px;">
                    <div style="font-size: 15px;margin-left: 8px;">
                        {{ index + 1 }}
                    </div>
                    <div class="labelblock">{{ item }}</div>
                    <i class="el-icon-close labelicon" @click="deletelabel(item)"></i>
                </div>
            </div>
            <i v-if="!addnewlabel" class="el-icon-circle-plus-outline labelicon" @click="addnewlabel = true"></i>
            <div v-else style="display: flex;flex-direction: column;justify-content: left;">
                <div style="display: flex;justify-content: left;align-items: center;">
                    <input placeholder="请输入新标签;不允许重复和空标签" v-model="newlabel" class="inputlabel">
                    <el-tooltip content="保存编辑" placement="top-start">
                        <i class="el-icon-check labelicon" @click="addsure"></i>
                    </el-tooltip>
                    <el-tooltip content="取消编辑" placement="top-end">
                        <i class="el-icon-close labelicon" @click="addcancel"></i>
                    </el-tooltip>
                </div>
                <span v-if="emptylabel" id="repeattext" class="animate__animated animate__shakeX">
                    {{ labelerror }}
                </span>
                <span v-else class="suretext" :class="{ addok: labelsure !== '待添加' }">
                    {{ labelsure }}
                </span>
            </div>
            <span slot="footer" class="dialog-footer">
                <el-button v-if="isupdate" size="mini" type="primary" @click="labelupdate">更新</el-button>
                <el-button size="mini" @click="labelcancel">关闭</el-button>
            </span>
        </el-dialog>
    </div>
</template>
<script>
import axios from 'axios'
export default {
    name: "TaskList",
    components: {

    },
    data() {
        return {
            newlabel: "",
            hideintroduction: false,
            createtask: [],
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
            update: false,
            show: {
                versionId: 0,
                labels: []
            },
            labelvisible: false,
            addnewlabel: false,
            emptylabel: false,
            labelerror: "",
            labelsure: "待添加",
            isupdate: false
        }
    },
    computed: {

    },
    methods: {
        addsure() {
            if (this.newlabel === "") {
                this.labelerror = "标签不能为空"
                this.emptylabel = true
            } else if (this.show.labels.includes(this.newlabel)) {
                this.labelerror = "标签重复"
                this.emptylabel = true
            } else {
                this.show.labels.push(this.newlabel)
                this.labelsure = "添加成功"
                this.newlabel = ""
                this.emptylabel = false
                this.isupdate = true
            }
        },
        deletelabel(item) {
            this.show.labels = this.show.labels.filter(element => {
                return item !== element
            })
            this.isupdate = true
        },
        addcancel() {
            this.newlabel = ""
            this.addnewlabel = false
            this.addnewlabel = false
            this.emptylabel = false
            this.labelerror = ""
            this.labelsure = "待添加"

        },
        labelupdate() {
            console.log(this.show);
            axios.post("http://192.168.224.150:10010/task/label", this.show).then(res => {
                console.log(res.data);
                this.$message.success("更新成功")
                this.handleTasklabel(this.show)
            })
        },
        labelcancel() {
            this.labelvisible = false
            this.addnewlabel = false
            this.emptylabel = false
            this.labelerror = ""
            this.labelsure = "待添加"
            this.show.labels = []
            this.show.versionId = 0
            this.isupdate = false
        },
        hide() {
            this.hideintroduction = !this.hideintroduction
        },
        getrowkey(row) {
            return row.userId || row.taskName
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
        },
        handleTasklabel(item) {
            axios.get("http://192.168.224.150:10010/task/label/" + item.versionId).then(res => {
                res.data.data.map(item => {
                    this.show.labels.push(item.label)
                })
                this.show.versionId = item.versionId
                this.labelvisible = true
            })
        },
        handleSchedule(item) {
            this.$router.push({ path: "/TaskSchedule/", query: { id: item.projectId, version: item.versionId } })
        },
        getcreatetask() {
            axios.get("http://192.168.224.150:10010/items/version").then(res => {
                console.log(res.data.data);
                this.createtask = res.data.data
            })
        }
    },
    mounted() {
        this.getcreatetask()
        this.update = !this.update
    },
}
</script>
<style scoped>
@import url('../../../node_modules/animate.css/animate.min.css');

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
.labelblock {
    border: 1px solid rgb(221, 221, 221);
    display: flex;
    justify-content: left;
    align-items: center;
    height: 30px;
    width: 240px;
    padding-left: 5px;
    cursor: pointer;
    margin-left: 22px;
}

.labelblock:hover {
    border: 1px solid rgb(36, 104, 242);
}

.labelicon {
    margin-left: 12px;
    cursor: pointer;
    font-size: 25px;
}

.labelicon:hover {
    color: rgb(36, 104, 242);
}

.inputlabel {
    width: 358px;
    height: 28px;
    display: flex;
    justify-content: left;
    align-items: center;
    padding-left: 5px;
    border-radius: 0px;
    border: 1px solid rgb(221, 221, 221);
    outline-style: none;
    font-size: 14px;
}

.inputlabel:focus {
    border: 1px solid rgb(36, 104, 242);
}

@keyframes shake {
    0% {
        transform: translate(0, 0);
    }

    10% {
        transform: translate(-5px, -5px);
    }

    20% {
        transform: translate(5px, 5px);
    }

    30% {
        transform: translate(-5px, -5px);
    }

    40% {
        transform: translate(5px, 5px);
    }

    50% {
        transform: translate(-5px, -5px);
    }

    60% {
        transform: translate(5px, 5px);
    }

    70% {
        transform: translate(-5px, -5px);
    }

    80% {
        transform: translate(5px, 5px);
    }

    90% {
        transform: translate(-5px, -5px);
    }

    100% {
        transform: translate(0, 0);
    }
}

#repeattext {
    animation: shake 0.8s 1 forwards;
    color: red;
    font-size: 18px;
    text-align: left;
}

.suretext {
    color: rgb(192, 196, 204);
    font-size: 18px;
    text-align: left;
}

.addok {
    color: green;
}
</style>