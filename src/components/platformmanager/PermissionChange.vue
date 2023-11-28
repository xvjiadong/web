<template>
    <div style="padding: 25px;margin-top: 15px;n">
        <el-table :data="list.slice((currentPage - 1) * pageSize, pageSize * currentPage)" :key="update">
            <el-table-column prop="userid" label="用户ID"></el-table-column>
            <el-table-column prop="username" label="用户名"></el-table-column>
            <el-table-column prop="company" label="所属公司"></el-table-column>
            <el-table-column prop="position" label="公司职位"></el-table-column>
            <el-table-column label="身份">
                <template slot-scope="scope">
                    <span>{{ scope.row.identity === 0 ? '数据标注员' : (scope.row.identity === 1 ? '项目管理员' : '平台管理员') }}</span>
                </template>
            </el-table-column>
            <el-table-column label="操作">
                <template slot-scope="scope">
                    <el-tooltip :content="scope.row.identity === 0 ? '升级权限' : '降低权限'" placement="left-start">
                        <el-button circle type="primary" @click="handlechange(scope.row)">
                            <i v-if="scope.row.identity === 0" style="font-size: 20px;" class="el-icon-upload2"></i>
                            <i v-else class="el-icon-download" style="font-size: 20px;"></i>
                        </el-button>
                    </el-tooltip>
                </template>
            </el-table-column>
        </el-table>
        <el-pagination style="margin-top: 25px;" :current-page="currentPage" :page-size="pageSize" background
            :page-sizes="[7, 20, 30]" layout="sizes, prev, pager, next, jumper" :total="list.length"
            @current-change="handleCurrentChange" @size-change="handleSizeChange" />
    </div>
</template>
<script>
export default {
    name: "PermissionChange",
    components: {

    },
    data() {
        return {
            dialogVisible: false,
            currentPage: 1,
            pageSize: 7,
            update: false,
            list: [
                {
                    userid: 13,
                    username: "小王",
                    company: "恒生电子",
                    position: "技术主管",
                    identity: 0,
                    
                },
                {
                    userid: 1,
                    username: "CoolCat99",
                    company: "云天科技",
                    position: "人力资源经理",
                    identity: 0
                },
                {
                    userid: 2,
                    username: "TechGuru23",
                    company: "坚实金融",
                    position: "市场营销专员",
                    identity: 1
                },
                {
                    userid: 3,
                    username: "HappyCoder7",
                    "company": "智慧电子",
                    "position": "软件工程师",
                    "identity": 0
                },
                {
                    "userid": 4,
                    "username": "DreamMaker",
                    "company": "创新科技",
                    "position": "产品经理",
                    "identity": 1
                },
                {
                    "userid": 5,
                    "username": "StarTraveller",
                    "company": "全球旅游",
                    "position": "导游",
                    "identity": 0
                },
                {
                    "userid": 6,
                    "username": "DataWhiz",
                    "company": "数码通信",
                    "position": "数据分析师",
                    "identity": 1
                },
                {
                    "userid": 7,
                    "username": "SportsFanatic",
                    "company": "体育传媒",
                    "position": "编辑记者",
                    "identity": 0
                },
                {
                    "userid": 8,
                    "username": "Fashionista",
                    "company": "时尚集团",
                    "position": "时装设计师",
                    "identity": 1
                },
                {
                    "userid": 9,
                    "username": "MusicLover",
                    "company": "音乐娱乐",
                    "position": "音乐制作人",
                    "identity": 0
                },
                {
                    "userid": 10,
                    "username": "ArtEnthusiast",
                    "company": "艺术画廊",
                    "position": "画廊经理",
                    "identity": 1
                }
            ],

        }
    },
    computed: {

    },
    methods: {
        handlechange(row) {
            row.identity = 1 - row.identity
        },
        handleSchedule(row) {
            this.list = this.list.filter(item => {
                return item.userid !== row.userid
            })
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
            return Math.floor(Math.random() * 5112 + 48525)
        },
        getuser() {
            for (let i = 0; i < Math.floor(Math.random() * 10 + 102); i++) {
                let a = {
                    userid: this.getnumber(),
                    username: this.getdescript(),
                    company: this.getdescript(),
                    position: this.getdescript(),
                    identity: Math.floor(Math.random() * 2)
                }
                this.list.push(a)
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