<template>
    <div class="container">
        <div class="header">
            <span style="font-size: 16px;color: rgb(21,27,38);">数据发布</span>
            <div style="display: flex;justify-content: space-between;">
                <span
                    style="font-size: 10px;color: rgb(21,27,38);">对于已通过审核的标注数据集，可以进行发布。数据集多次发布，数据集每次发布都会生成一个唯一的发布版本号，发布时为数据集生成当前的数据快照，并进行存储，发布的数据快照不可进行修改</span>
                <span class="hide" @click="hideintroduction = !hideintroduction">
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
                        恒生电子数据标注平台为一站式数据处理和服务平台，数据发布导出需要得到权限
                    </span>
                </div>
            </div>
            <div class="teachbody">
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/任务1.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            选择可发布版本
                        </div>
                        <div class="itemcontent">
                            您只可选择由您创建的、已完成标注和审核的数据集版本进行发布
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/任务2.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            发布数据
                        </div>
                        <div class="itemcontent">
                            数据集每次发布都会生成一个唯一的发布版本号，发布时为数据集生成当前的数据快照，数据快照不可进行修改
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/任务3.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            数据导出
                        </div>
                        <div class="itemcontent">
                            具备权限的用户可以导出已发布的数据集。
                        </div>
                    </div>
                </div>
            </div>
        </el-card>
        <div>
            <el-table :data="publish" :row-key="getrowkey" :key="update">
                <el-table-column type="expand" width="75" label="已发布">
                    <template slot-scope="scope">
                        <div style="text-align:center" v-if="scope.row.published.length > 0">
                            <el-table :data="scope.row.published" :row-key="getrowkey">
                                <el-table-column prop="publishnumber" width="105" label="发布号"></el-table-column>
                                <el-table-column prop="publishdescript" label="发布数据描述"></el-table-column>
                                <el-table-column prop="dataNumber" label="发布数据量"></el-table-column>
                                <el-table-column prop="publishTime" label="发布时间"></el-table-column>
                                <el-table-column label="操作">
                                    <template slot-scope="scope2">
                                        <el-button size="mini" @click="handleout(scope2.row)">导出</el-button>
                                        <el-button size="mini" @click="handle(scope2.row)">删除</el-button>
                                    </template>
                                </el-table-column>
                            </el-table>
                        </div>
                        <div style="text-align:center; " v-else>
                            <el-empty description="未发布数据" style="padding:0px;color:rgb(21,27,38)">
                            </el-empty>
                        </div>
                    </template>
                </el-table-column>
                <el-table-column label="所属项目名" prop="projectName"></el-table-column>
                <el-table-column label="项目版本" prop="verName"></el-table-column>
                <el-table-column label="当前数据量" prop="dataNumber"></el-table-column>
                <el-table-column label="最后发布时间" prop="lastPublishtime"></el-table-column>
                <el-table-column label="数据类型" prop="dataType"></el-table-column>
                <el-table-column label="标注类型" prop="callType"></el-table-column>
                <el-table-column label="操作">
                    <template slot-scope="scope">
                        <el-button size="mini" @click="handlepublish(scope.row)">发布</el-button>
                        <el-button size="mini" @click="handle(scope.row)">查看</el-button>
                    </template>
                </el-table-column>
            </el-table>
        </div>
        <el-dialog width="24%" top="15%" title="发布选中数据集" :visible.sync="publishvis" :destroy-on-close="true"
            :show-close="false" :close-on-click-modal="false">
            <div>确定发布当前数据集吗？发布后若对数据二次操作，请重新发布</div>
            <span slot="footer" class="dialog-footer">
                <el-button size="mini" type="primary" @click="publishok">确 定</el-button>
                <el-button size="mini" @click="publishcancel">取 消</el-button>
            </span>
        </el-dialog>
    </div>
</template>
<script>
export default {
    name: "DataPublish",
    components: {

    },
    data() {
        return {
            publishvis: false,
            update: false,
            hideintroduction: false,
            publish: [
                {
                    projectid: 1,
                    projectName: "财务大厅文本",
                    verName: "V1",
                    lastPublishtime: "2023-11-21 21:00:00",
                    dataType: "图像",
                    callType: "图像文本标注",
                    dataNumber: 50,
                    published: [
                        {
                            publishTime: "2023-11-21 18:00:00",
                            publishnumber: 1,
                            publishdescript: "初版",
                            dataNumber: 50
                        },
                        {
                            publishTime: "2023-11-21 19:00:00",
                            publishnumber: 2,
                            publishdescript: "数据增加板",
                            dataNumber: 418
                        },
                        {
                            publishTime: "2023-11-21 20:00:00",
                            publishnumber: 3,
                            publishdescript: "简略版",
                            dataNumber: 44
                        },
                        {
                            publishTime: "2023-11-21 21:00:00",
                            publishnumber: 4,
                            publishdescript: "终版",
                            dataNumber: 68
                        },
                    ]
                },
                {
                    projectid: 2,
                    projectName: "公司合同",
                    verName: "V1",
                    dataNumber: 50,
                    lastPublishtime: "2023-11-24 15:02:23",
                    dataType: "文本",
                    callType: "信息抽取标注",
                    published: [
                        {
                            publishTime: "2023-11-21 18:00:00",
                            publishnumber: 5,
                            publishdescript: "初版",
                            dataNumber: 50
                        },
                        {
                            publishTime: "2023-11-21 19:00:00",
                            publishnumber: 6,
                            publishdescript: "数据增加板",
                            dataNumber: 418
                        },
                        {
                            publishTime: "2023-11-21 20:00:00",
                            publishnumber: 7,
                            publishdescript: "简略版",
                            dataNumber: 44
                        },
                        {
                            publishTime: "2023-11-21 21:00:00",
                            publishnumber: 8,
                            publishdescript: "终版",
                            dataNumber: 68
                        },
                    ]
                },
                {
                    projectid: 3,
                    projectName: "条款分类",
                    verName: "V1",
                    dataNumber: 50,
                    lastPublishtime: "2023-11-27 12:32:15",
                    dataType: "图像",
                    callType: "图片分类标注",
                    published: [
                        {
                            publishTime: "2023-11-21 18:00:00",
                            publishnumber: 9,
                            publishdescript: "初版",
                            dataNumber: 50
                        },
                        {
                            publishTime: "2023-11-21 19:00:00",
                            publishnumber: 10,
                            publishdescript: "数据增加板",
                            dataNumber: 418
                        },
                        {
                            publishTime: "2023-11-21 20:00:00",
                            publishnumber: 11,
                            publishdescript: "简略版",
                            dataNumber: 44
                        },
                        {
                            publishTime: "2023-11-21 21:00:00",
                            publishnumber: 12,
                            publishdescript: "终版",
                            dataNumber: 68
                        },
                    ]
                },
                {
                    projectid: 4,
                    projectName: "报表分类",
                    verName: "V1",
                    dataNumber: 50,
                    lastPublishtime: "2023-11-24 09:15:24",
                    dataType: "文本",
                    callType: "文本分类标注",
                    published: [
                        {
                            publishTime: "2023-11-21 18:00:00",
                            publishnumber: 13,
                            publishdescript: "初版",
                            dataNumber: 50
                        },
                        {
                            publishTime: "2023-11-21 19:00:00",
                            publishnumber: 14,
                            publishdescript: "数据增加板",
                            dataNumber: 418
                        },
                        {
                            publishTime: "2023-11-21 20:00:00",
                            publishnumber: 15,
                            publishdescript: "简略版",
                            dataNumber: 44
                        },
                        {
                            publishTime: "2023-11-21 21:00:00",
                            publishnumber: 16,
                            publishdescript: "终版",
                            dataNumber: 68
                        },
                    ]
                },
                {
                    projectid: 5,
                    projectName: "财务报表文字数据",
                    verName: "V2",
                    dataNumber: 50,
                    lastPublishtime: "2023-11-21 18:23:37",
                    dataType: "图像",
                    callType: "图像文本标注",
                    published: [
                        {
                            publishTime: "2023-11-21 18:00:00",
                            publishnumber: 17,
                            publishdescript: "初版",
                            dataNumber: 50
                        },
                        {
                            publishTime: "2023-11-21 19:00:00",
                            publishnumber: 18,
                            publishdescript: "数据增加板",
                            dataNumber: 418
                        },
                        {
                            publishTime: "2023-11-21 20:00:00",
                            publishnumber: 19,
                            publishdescript: "简略版",
                            dataNumber: 44
                        },
                        {
                            publishTime: "2023-11-21 21:00:00",
                            publishnumber: 20,
                            publishdescript: "终版",
                            dataNumber: 68
                        },
                    ]
                },
                {
                    projectid: 6,
                    projectName: "基金合同",
                    verName: "V2",
                    dataNumber: 50,
                    lastPublishtime: "2023-11-27 21:08:50",
                    dataType: "文本",
                    callType: "信息抽取标注",
                    published: [
                        {
                            publishTime: "2023-11-21 18:00:00",
                            publishnumber: 21,
                            publishdescript: "初版",
                            dataNumber: 50
                        },
                        {
                            publishTime: "2023-11-21 19:00:00",
                            publishnumber: 22,
                            publishdescript: "数据增加板",
                            dataNumber: 418
                        },
                        {
                            publishTime: "2023-11-21 20:00:00",
                            publishnumber: 23,
                            publishdescript: "简略版",
                            dataNumber: 44
                        },
                        {
                            publishTime: "2023-11-21 21:00:00",
                            publishnumber: 24,
                            publishdescript: "终版",
                            dataNumber: 68
                        },
                    ]
                },
                {
                    projectid: 7,
                    dataNumber: 50,
                    projectName: "ocr数据",
                    verName: "V2",
                    lastPublishtime: "2023-11-14 08:51:22",
                    dataType: "图像",
                    callType: "图片分类标注",
                    published: [
                        {
                            publishTime: "2023-11-21 18:00:00",
                            publishnumber: 25,
                            publishdescript: "初版",
                            dataNumber: 50
                        },
                        {
                            publishTime: "2023-11-21 19:00:00",
                            publishnumber: 26,
                            publishdescript: "数据增加板",
                            dataNumber: 418
                        },
                        {
                            publishTime: "2023-11-21 20:00:00",
                            publishnumber: 27,
                            publishdescript: "简略版",
                            dataNumber: 44
                        },
                        {
                            publishTime: "2023-11-21 21:00:00",
                            publishnumber: 28,
                            publishdescript: "终版",
                            dataNumber: 68
                        },
                    ]
                },
                {
                    projectid: 8,
                    projectName: "智能驾驶数据",
                    verName: "V2",
                    lastPublishtime: "2023-11-28 08:23:14",
                    dataType: "文本",
                    dataNumber: 50,
                    callType: "文本分类标注",
                    published: [
                        {
                            publishTime: "2023-11-21 18:00:00",
                            publishnumber: 29,
                            publishdescript: "初版",
                            dataNumber: 50
                        },
                        {
                            publishTime: "2023-11-21 19:00:00",
                            publishnumber: 30,
                            publishdescript: "数据增加板",
                            dataNumber: 418
                        },
                        {
                            publishTime: "2023-11-21 20:00:00",
                            publishnumber: 31,
                            publishdescript: "简略版",
                            dataNumber: 44
                        },
                        {
                            publishTime: "2023-11-21 21:00:00",
                            publishnumber: 32,
                            publishdescript: "终版",
                            dataNumber: 68
                        },
                    ]
                },
                {
                    projectid: 9,
                    dataNumber: 50,
                    projectName: "标准数据",
                    verName: "V3",
                    lastPublishtime: "2023-11-13 20:04:00",
                    dataType: "文本",
                    callType: "文本分类标注",
                    published: [
                    ]
                },
            ],
            choose: ""
        }
    },
    computed: {

    },
    methods: {
        generateUID() {
            var timestamp = new Date().getTime();
            var uid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
                var r = (timestamp + Math.random() * 16) % 16 | 0;
                timestamp = Math.floor(timestamp / 16);
                return (c === 'x' ? r : (r & 0x3 | 0x8)).toString(16);
            });
            return uid;
        },
        handleout(row) {
            console.log(row);
            let a = document.createElement("a")
            a.href = "https://items-storage.oss-cn-beijing.aliyuncs.com/pjp/%E8%B4%A6%E5%8A%A1%E5%90%88%E5%90%8C%E6%96%87%E6%9C%AC.zip"
            a.click()
            a.remove()
        },
        getrowkey(row) {
            return row.projectid || row.publishnumber
        },
        handle(row) {
            console.log(row);
        },
        handlepublish(row) {
            this.publishvis = true
            this.choose = row
        },
        publishok() {
            let a = {
                publishTime: this.gettime(),
                publishnumber: this.generateUID(),
                publishdescript: "二次修订版",
                dataNumber: this.choose.dataNumber
            }
            this.publish.map(item => {
                if (item.projectid === this.choose.projectid) {
                    item.published.push(a)
                    item.dataNumber += 1
                    item.lastPublishtime=this.gettime()
                }
            })
            this.update = !this.update
            this.publishcancel()
        },
        publishcancel() {
            this.choose = ""
            this.publishvis = false
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
        }
    },
    mounted() {
        this.publish.map(item => {
            item.published.map(item => {
                item.publishnumber=this.generateUID()
            })
        })
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

.hide {
    font-size: 10px;
    color: #84868c;
    cursor: pointer;
}

.hide:hover {
    color: blue;
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