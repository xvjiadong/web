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
                        鼠标标注平台,一站式数据处理和服务平台
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
        <el-card v-for="(item) in publishlist" :key="item.id + '-' + item.name" class="teachcard">
            <div slot="header">
                <div style="text-align: left;">
                    <span style="font-size: 18px;color: rgb(21,27,38);">{{ item.name }}</span>&emsp;
                </div>
            </div>
            <el-table :data="item.versions">
                <el-table-column prop="verName" label="版本号"></el-table-column>
                <el-table-column prop="callType" label="标注类型"></el-table-column>
                <el-table-column prop="dataNumber" label="数据量"></el-table-column>
                <el-table-column label="操作">
                    <template slot-scope="scope">
                        <el-button type="primary" @click="publish(item, scope.row)" size="small"
                            style="font-size: 15px;">发布</el-button>
                    </template>
                </el-table-column>
            </el-table>
        </el-card>
        <el-pagination :current-page="page" background layout="prev, pager, next" :page-size="5" :page-count="total">
        </el-pagination>
    </div>
</template>
<script>
import axios from 'axios'
export default {
    name: "DataPublish",
    components: {

    },
    data() {
        return {
            hideintroduction: false,
            page: 1,
            publishlist: [],
            total: 0
        }
    },
    computed: {

    },
    methods: {
        pagechange(i) {
            if (!(this.page + i)) {
                this.$message.warning("已经是第一页了")
            } else {
                this.getpublish(this.page + i)
            }
        },
        publish(item, row) {
            console.log(row);
            this.$router.push({
                path: "/publishdetail",
                query: {
                    id: item.id,
                    name: item.name,
                    versionId: row.versionId,
                    verName: item.verName
                }
            })
        },
        getpublish(page) {
            axios.post("http://120.26.142.114:10010/items/version/finish", { current: page, pageSize: 5 })
                .then(res => {
                    console.log(res.data)
                    if (res.data.data.list.length > 0) {
                        this.publishlist = res.data.data.list
                        this.page = page
                        this.total = res.data.data.total
                    } else {
                        this.$message.warning("已经是最后一页了")
                    }
                }).catch(e => {
                    console.log(e);
                })
        }
    },
    mounted() {
        this.getpublish(this.page)
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