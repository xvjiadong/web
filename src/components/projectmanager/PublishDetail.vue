<template>
    <div style="width: 95%;margin-top: 2%;">
        <el-card class="box-card">
            <div slot="header" class="cardheader">
                <el-page-header @back="goBack" :content="version.name + '-' + version.verName">
                </el-page-header>
            </div>
            <el-table :data="versionlist" border>
                <el-table-column prop="time" label="发布时间"></el-table-column>
                <el-table-column prop="description" label="数据集描述"></el-table-column>
                <el-table-column label="操作">
                    <template slot-scope="scope">
                        <el-button @click="download(scope.row.url)" size="small" style="font-size: 15px;">下载</el-button>
                    </template>
                </el-table-column>
            </el-table>
            <span @click="publishvis = true" class="publish">发布数据集</span>
        </el-card>
        <el-dialog width="40%" top="15%" title="选择导出格式" :visible.sync="publishvis" :destroy-on-close="true"
            :show-close="false" :close-on-click-modal="false">
            <el-checkbox-group v-model="format">
                <el-checkbox label="coco"></el-checkbox>
                <el-checkbox label="yolo"></el-checkbox>
                <el-checkbox label="voc"></el-checkbox>
            </el-checkbox-group>
            <el-input v-model="descript" type="textarea" placeholder="请输入该次导出数据集描述"></el-input>
            <span slot="footer" class="dialog-footer">
                <el-button :disabled="format.length == 0" size="mini" type="primary" @click="publishok">确 定</el-button>
                <el-button size="mini" @click="publishcancel">取 消</el-button>
            </span>
        </el-dialog>
    </div>
</template>
<script>
import axios from 'axios'
export default {
    data() {
        return {
            version: {
                id: "",
                versionId: "",
                verName: "",
                task: ""
            },
            versionlist: [],
            publishvis: false,
            format: [],
            descript: ""
        }
    },
    methods: {
        publishok() {

            this.$message.info("正在准备发布中，请稍等")
            axios.post("http://localhost:5000/api/data_publish", { id: this.version.versionId, format: this.format, descript: this.descript, task: this.version.task })
                .then(res => {
                    if (res.data == 'ok') {
                        this.geturl(this.version.versionId)
                    }
                }).catch(e => {
                    console.log(e);
                })
            this.publishcancel()
        },
        publishcancel() {
            this.descript = ""
            this.format = []
            this.publishvis = false
        },
        download(url) {
            let a = document.createElement("a")
            a.href = url
            a.download = url.split("/")[url.split("/").length - 1]
            a.click()
        },
        goBack() {
            this.$router.push("/DataPublish")
        },
        geturl(id) {
            axios.get("http://120.26.142.114:10010/dataset/url/?id=" + id)
                .then(res => {
                    console.log(res.data);
                    if (res.data.code === 200) {
                        this.versionlist = res.data.data
                    }
                }).catch(e => {
                    console.log(e);
                })
        }
    },
    mounted() {
        let query = this.$route.query
        this.version.id = query.id - 0
        this.version.name = query.name
        this.version.versionId = query.versionId - 0
        this.version.verName = query.verName
        this.version.task = query.task
        this.geturl(this.version.versionId)
    },
}
</script>
<style scoped>
.box-card {
    width: 100%;
    margin-left: 1%;
    height: 600px;
}

.cardheader {
    display: flex;
    justify-content: left;
    padding-left: 15px;
    align-items: center;
    font-size: 25px;
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

.publish {
    cursor: pointer;
}

.publish:hover {
    color: rgb(36, 104, 242);
    text-decoration: underline;
}
</style>
