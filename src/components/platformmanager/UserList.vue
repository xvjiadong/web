<template>
    <div style="margin-top: 15px;padding: ;">
        <el-table :data="user.slice((currentPage - 1) * pageSize, pageSize * currentPage)" :key="update">
            <el-table-column prop="userid" label="用户ID"></el-table-column>
            <el-table-column prop="username" label="用户名"></el-table-column>
            <el-table-column label="身份">
                <template slot-scope="scope">
                    <span>{{ scope.row.identity === 0 ? '数据标注员' : (scope.row.identity === 1 ? '项目管理员' : '平台管理员') }}</span>
                </template>
            </el-table-column>
            <el-table-column prop="dealdatanumber" label="标注数据数量"></el-table-column>
            <el-table-column prop="nowtask" label="现有未完成任务"></el-table-column>
            <el-table-column prop="completed" label="已完成任务"></el-table-column>
            <el-table-column label="操作">
                <template slot-scope="scope">
                    <el-tooltip placement="left">
                        <div slot="content">
                            <div>标注合格率：92%</div>
                            <div>累积参与项目：68</div>
                            <div>累积完成任务：458</div>
                            <div>团队满意度：85%</div>
                            <div>一次性最高标注个数：3000</div>
                            <div>上次标注时间：2023-11-22 18:00</div>
                            <div>范例文件个数：150</div>
                        </div>
                        <i class="el-icon-info"></i>
                    </el-tooltip>
                    <span class="tableplay" @click="handleSchedule(scope.row)">配权</span>
                    <span class="tableplay" @click="handleSchedule(scope.row)">调度</span>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination :current-page="currentPage" :page-size="pageSize" background :page-sizes="[11, 20, 30]"
            layout="sizes, prev, pager, next, jumper" :total="user.length" @current-change="handleCurrentChange"
            @size-change="handleSizeChange" />
    </div>
</template>
<script>
export default {
    name: "UserList",
    components: {

    },
    data() {
        return {
            currentPage: 1,
            pageSize: 11,
            user: [
                {
                    userid: 1,
                    username: "小王",
                    identity: 0,
                    dealdatanumber: this.getnumber(),
                    nowtask: this.getnumber(),
                    completed: this.getnumber()
                },
                {
                    userid: 2,
                    username: "小李",
                    identity: 1,
                    dealdatanumber: this.getnumber(),
                    nowtask: this.getnumber(),
                    completed: this.getnumber()
                },
                {
                    userid: 3,
                    username: "官方",
                    identity: 1,
                    dealdatanumber: this.getnumber(),
                    nowtask: this.getnumber(),
                    completed: this.getnumber()
                },
                {
                    userid: 4,
                    username: "规范",
                    identity: 1,
                    dealdatanumber: this.getnumber(),
                    nowtask: this.getnumber(),
                    completed: this.getnumber()
                },
                {
                    userid: 5,
                    username: "凌风",
                    identity: 1,
                    dealdatanumber: this.getnumber(),
                    nowtask: this.getnumber(),
                    completed: this.getnumber()
                },
                {
                    userid: 6,
                    username: "呜呜",
                    identity: 0,
                    dealdatanumber: this.getnumber(),
                    nowtask: this.getnumber(),
                    completed: this.getnumber()
                },
                {
                    userid: 7,
                    username: "小李",
                    identity: 0,
                    dealdatanumber: this.getnumber(),
                    nowtask: this.getnumber(),
                    completed: this.getnumber()
                },
                {
                    userid: 8,
                    username: "小该",
                    identity: 0,
                    dealdatanumber: this.getnumber(),
                    nowtask: this.getnumber(),
                    completed: this.getnumber()
                },
                {
                    userid: 9,
                    username: "小顾",
                    identity: Math.floor(Math.random() * 2),
                    dealdatanumber: this.getnumber(),
                    nowtask: this.getnumber(),
                    completed: this.getnumber()
                },
                {
                    userid: 10,
                    username: "小豪",
                    identity: 0,
                    dealdatanumber: this.getnumber(),
                    nowtask: this.getnumber(),
                    completed: this.getnumber()
                },
                {
                    userid: 11,
                    username: "萧炎",
                    identity: 0,
                    dealdatanumber: this.getnumber(),
                    nowtask: this.getnumber(),
                    completed: this.getnumber()
                }
            ],
            update: false
        }
    },
    computed: {

    },
    methods: {
        handleSchedule(row) {
            console.log(row);
        },
        handleSizeChange(val) {
            this.pageSize = val
        },
        handleCurrentChange(val) {
            this.currentPage = val
        },
        getdescript() {
            let a = ""
            for (let i = 0; i < (Math.floor(Math.random() * 5 + 5)); i++) {
                const start = 0x4e00;
                const end = 0x9fa5;
                const randomCode = Math.floor(Math.random() * (end - start) + start);
                const randomChar = String.fromCharCode(randomCode);
                a += randomChar
            }
            return a;
        },
        gettime() {
            const now = new Date(); // 获取当前时间
            const year = now.getFullYear(); // 年
            const month = String(now.getMonth() + 1).padStart(2, '0'); // 月，需要补0
            const date = String(now.getDate()).padStart(2, '0'); // 日，需要补0
            const hour = String(now.getHours()).padStart(2, '0'); // 小时，需要补0
            const minute = String(now.getMinutes()).padStart(2, '0'); // 分钟，需要补0
            const second = String(now.getSeconds()).padStart(2, '0'); // 秒，需要补0

            // 拼接成需要的格式
            const currentTime = `${year}-${month}-${date} ${hour}:${minute}:${second}`;
            return currentTime
        },
        getnumber() {
            return Math.floor(Math.random() * 51 + 45)
        },
        getuser() {
            for (let i = 0; i < Math.floor(Math.random() * 10 + 102); i++) {
                let a = {
                    userid: this.getnumber(),
                    username: this.getdescript(),
                    identity: Math.floor(Math.random() * 2),
                    dealdatanumber: this.getnumber(),
                    nowtask: this.getnumber(),
                    completed: this.getnumber()
                }
                this.user.push(a)
            }
            this.update = !this.update
        }
    },
    mounted() {
        this.getuser()
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