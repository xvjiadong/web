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
                            选择标注任务
                        </div>
                        <div class="itemcontent">
                            选择接受的标注任务
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/任务2.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            数据标注
                        </div>
                        <div class="itemcontent">
                            选择任务后进入标注界面进行数据标注任务，主要为信息抽取标注、文本分类标注、图像文本标注、图片分类标注四大类型
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/任务3.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            提交审核
                        </div>
                        <div class="itemcontent">
                            完成该任务的标注后提交任务，将该任务交由任务发布者审核
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/pickind.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            任务移交
                        </div>
                        <div class="itemcontent">
                            任务过程中出现问题支持数据标注员选择新的数据标注员移交任务
                        </div>
                    </div>
                </div>
            </div>
        </el-card>
        <el-card class="teachcard">
            <div slot="header" style="display: flex;justify-content: space-between;align-items:center">
                <el-menu :default-active="'accpet'" mode="horizontal">
                    <el-menu-item index="accpet" @click="mode = 1">接受的任务</el-menu-item>
                </el-menu>
            </div>
            <div>
                <el-table ref="accept" :data="accepttask">
                    <el-table-column type="expand" width="0"></el-table-column>
                    <el-table-column width="150" prop="taskName" label="任务名称"></el-table-column>
                    <el-table-column width="120" prop="projectName" label="所属项目"></el-table-column>
                    <el-table-column width="120" prop="version" label="所属版本"></el-table-column>
                    <el-table-column width="120" prop="adminNane" label="任务创建者"></el-table-column>
                    <el-table-column width="80" prop="dataNumber" label="数据量"></el-table-column>
                    <el-table-column width="80" prop="progress" label="标注进度"></el-table-column>
                    <el-table-column width="150" prop="callType" label="标注类型"></el-table-column>
                    <el-table-column width="150" prop="startTime" label="创建时间"></el-table-column>
                    <el-table-column width="150" prop="endTime" label="截止时间"></el-table-column>
                    <el-table-column label="操作">
                        <template slot-scope="scope">
                            <span size="mini" class="tableplay" v-if="scope.row.taskprocess !== '100%'"
                                @click="push(scope.row)">标注</span>
                            <span size="mini" class="tableplay" v-if="scope.row.taskprocess === '100%'"
                                @click="review(scope.row)">提交审核</span>
                            <span size="mini" class="tableplay" @click="turn(scope.row)">转让</span>
                        </template>
                    </el-table-column>
                </el-table>
            </div>
        </el-card>
    </div>
</template>
<script>
import axios from 'axios'
export default {
    name: "MakeMark",
    components: {

    },
    data() {
        return {
            hideintroduction: false,
            accepttask: [

            ],
        }
    },
    computed: {

    },
    methods: {
        push(row) {
            console.log(row);
            if (row.pre === 'ing') {
                this.$message.error("正在进行一键标注，请不要进入标注界面")
                return
            }
            let router
            if (row.callType === "图像文本标注") {
                router = "/PicView"
            } else if (row.callType === "信息抽取标注") {
                router = "/PdfView"
            } else if (row.callType.includes("图片分类标注")) {
                router = "/ImageClassification"
            } else if (row.callType === "文本分类" || row.callType === "新闻分类" || row.callType === "情感分析" || row.callType === "意图识别") {
                router = "/TextClassification"
            } else if (row.callType === "分割标注") {
                router = "/segment"
            } else if (row.callType === "物体检测") {
                router = "/detect"
            } else if (row.callType === "实体识别") {
                router = "/entity"
            } else if (row.callType === "关键词抽取" || row.callType === "生成式摘要") {
                router = "/keyandsummary"
            } else if (row.callType === "自然语言推理") {
                router = "/languageinference"
            } else if (row.callType === "抽取式阅读理解") {
                router = "/readview"
            }
            this.$router.push({
                path: router,
                query: row
            })
        },
        hide() {
            this.hideintroduction = !this.hideintroduction
        },
        review(item) {
            console.log(item);
        },
        turn(item) {
            console.log(item);
        },
        gettask() {
            axios.get("http://120.26.142.114:10010/task/user").then((res) => {
                console.log(res.data);
                this.accepttask = res.data.data
            })
        }
    },
    mounted() {
        this.gettask()
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