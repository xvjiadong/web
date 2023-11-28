<template>
    <div style="margin-top: 15px;padding: 15px;">
        <el-table :data="project">
            <el-table-column prop="projectName" label="项目名称"></el-table-column>
            <el-table-column prop="belongname" label="项目所有人"></el-table-column>
            <el-table-column prop="version" label="项目版本数量"></el-table-column>
            <el-table-column prop="task" label="项目任务数量"></el-table-column>
            <el-table-column prop="lastdealtime" label="最后处理时间"></el-table-column>
            <el-table-column label="操作">
                <template slot-scope="scope">
                    <el-tooltip placement="left">
                        <div slot="content">
                            <div>标注数据类型：图像</div>
                            <div>标注任务类型：物体检测/文本监测/图片分类</div>
                            <div>最后处理时间：{{ scope.row.lastdealtime }}</div>
                            <div>最新版本标注进度：35%</div>
                            <div>最新进度：已发布5个版本/待发布10个版本/待标注15个版本</div>
                            <div>标注情况：合格率95%/不合格率5%/退回率12%/未完成率15%</div>
                            <div>标注团队：已经手3个团队，平均每个团队5名成员</div>
                        </div>
                        <i class="el-icon-info"></i>
                    </el-tooltip>
                    <span class="tableplay" @click="handleSchedule(scope.row)">调度</span>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination background layout="prev, pager, next" :total="1000">
        </el-pagination>
    </div>
</template>
<script>
export default {
    name: "ProjectList",
    components: {

    },
    data() {
        return {
            project: [
                {
                    projectId: 1,
                    projectName: "ocr图像",
                    belongid: "1",
                    belongname: "小王",
                    version: 20,
                    task: 15,
                    lastdealtime: "2023-11-22 23:00"
                },
                {
                    projectId: 2,
                    projectName: "无人驾驶标注数据",
                    belongid: "2",
                    belongname: "小刘",
                    version: 20,
                    task: 15,
                    lastdealtime: "2023-11-22 23:00",
                },
                {
                    projectId: 3,
                    projectName: "财务报表数据",
                    belongid: "3",
                    belongname: "小徐",
                    version: 20,
                    task: 15,
                    lastdealtime: "2023-11-22 23:00",
                },
                {
                    projectId: 4,
                    projectName: "场景物体数据",
                    belongid: "4",
                    belongname: "小吴",
                    version: 20,
                    task: 15,
                    lastdealtime: "2023-11-22 23:00",
                },
                {
                    projectId: 5,
                    projectName: "法律条款数据",
                    belongid: "5",
                    belongname: "小夫",
                    version: 20,
                    task: 15,
                    lastdealtime: "2023-11-22 23:00",
                },
                {
                    projectId: 6,
                    projectName: "合同数据",
                    belongid: "6",
                    belongname: "无误",
                    version: 20,
                    task: 15,
                    lastdealtime: "2023-11-22 23:00",
                },
                {
                    projectId: 7,
                    projectName: "金融数据",
                    belongid: "7",
                    belongname: "雨巷",
                    version: 20,
                    task: 15,
                    lastdealtime: "2023-11-22 23:00",
                },
                {
                    projectId: 8,
                    projectName: "道路物体数据",
                    belongid: "8",
                    belongname: "萧炎",
                    version: 20,
                    task: 15,
                    lastdealtime: "2023-11-22 23:00",
                },
                {
                    projectId: 9,
                    projectName: "测试数据",
                    belongid: "9",
                    belongname: "小五",
                    version: 20,
                    task: 15,
                    lastdealtime: "2023-11-22 23:00",
                },
                {
                    projectId: 1,
                    projectName: "屏幕数据",
                    belongid: "1",
                    belongname: "福贵",
                    version: 20,
                    task: 15,
                    lastdealtime: "2023-11-22 23:00",
                }
            ]
        }
    },
    computed: {

    },
    methods: {

    },
    mounted() {

    },
}
</script>
<style scoped>
.tableplay {
    margin-left: 8px;
    color: rgb(26, 115, 232);
    font-size: 12px;
    cursor: pointer;
}

.tableplay:hover {
    color: rgb(82, 142, 255);
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
</style>