<template>
    <div>
        <el-page-header @back="goBack">
        </el-page-header>
        <div v-loading="loading" style="height: 480px;padding: 25px;">
            <div v-for="(item, index) in showlist" :key="item.ossPath" class="card">
                <img class="pic" :src="item.ossPath">
                <el-divider direction="vertical"></el-divider>
                <div style="width: 85%;">
                    <div v-if="item.pic.length > 0" class="generate_block">
                        <div
                            style="display: flex;justify-content: space-between;padding-left: 15px;padding-right: 15px;">
                            <el-checkbox :indeterminate="isIndeterminate" v-model="checkAll"
                                @change="handleCheckAllChange($event, item.pic, index)">全选</el-checkbox>
                            <span @click="submit(item.id, item.choice)" class="submit">提交</span>
                        </div>
                        <el-divider></el-divider>
                        <el-checkbox-group @change="handleCheckedCitiesChange($event, item.pic)" v-model="item.choice"
                            style="display: flex;overflow-x: auto;">
                            <el-checkbox :label="image.id" v-for="image in item.pic"
                                :key="image.ossPath + '-' + image.id">
                                <img :src="image.ossPath" class="generate_pic">
                            </el-checkbox>
                        </el-checkbox-group>
                    </div>
                    <el-empty v-else description="该图片未作为样本生成过图片"></el-empty>
                </div>
            </div>
            <el-pagination v-if="showlist.length !== 0" :hide-on-single-page="true" :current-page="page"
                :page-sizes="[5]" :page-size="5" background layout="sizes, prev, pager, next, jumper" :total="total"
                @current-change="handleCurrentChange" />
        </div>
    </div>

</template>
<script>
import axios from 'axios'
export default {
    data() {
        return {
            version: {
                dataId: 0,
                ids: []
            },
            versionId: 0,
            page: 1,
            showlist: [

            ],
            total: 0,
            loading: false,
            loadingnum: 0,
            checkAll: false,
            isIndeterminate: true
        }
    },
    methods: {
        goBack() {
            this.$router.push("/projectlist")
        },
        submit(id, ids) {
            axios.post("http://120.26.142.114:10010/dataset/temp", { "ids": ids, "dataId": id })
                .then(res => {
                    if (res.data.code === 200) {
                        this.getdata(this.page)
                    }
                })
                .catch(e => {
                    console.log(e);
                })
        },
        handleCheckAllChange(val, pic, index) {
            if (val) {
                pic.forEach(item => {
                    this.showlist[index].choice.push(item.id)
                })
            } else {
                this.showlist[index].choice = []
            }
            this.isIndeterminate = false;
        },
        handleCheckedCitiesChange(value, pic) {
            let checkedCount = value.length;
            this.checkAll = checkedCount === pic.length;
            this.isIndeterminate = checkedCount > 0 && checkedCount < pic.length;
        },
        handleCurrentChange(val) {
            this.getdata(val)
        },
        getpic(id, index) {
            axios.get("http://120.26.142.114:10010/dataset/temp?id=" + id)
                .then(res => {
                    if (res.data.code === 200) {
                        this.showlist[index].pic = res.data.data
                    }
                    this.loadingnum += 1
                    if (this.loadingnum === this.showlist.length) {
                        //console.log(this.showlist);
                        this.loading = false
                    }
                }).catch(e => {
                    console.log(e);
                })
        },
        getdata(page) {
            this.loading = true
            this.loadingnum = 0
            axios.post("http://120.26.142.114:10010/dataset/admin/select", { current: page, pageSize: 5, version: this.version.versionId })
                .then(res => {
                    if (res.data.code === 200) {
                        this.showlist.concat(res.data.data.datasetCallNewVOS)
                        this.showlist = res.data.data.datasetCallNewVOS
                        this.total = res.data.data.total
                        this.showlist.forEach((item, index) => {
                            item.pic = []
                            this.getpic(item.id, index)
                        })
                    }
                })
                .catch(e => {
                    console.log(e);
                })
        }
    },
    mounted() {
        this.version.versionId = this.$route.query.versionId - 0
        this.getdata(this.page)
    }
}
</script>

<style scoped>
.card {
    display: flex;
    width: 95%;
    justify-content: flex-start;
    align-items: center;
    padding: 25px;
    background-color: rgb(210, 220, 220);
}

.card:nth-child(n+2) {
    margin-top: 10px;
}

.pic {
    width: 270px;
    height: 270px;
}

.generate_block {
    width: 90%;
}

.generate_pic {
    width: 220px;
    height: 220px;
}

.generate_pic:nth-child(n+2) {
    margin-left: 35px;
}

/deep/.el-divider--horizontal {
    display: block;
    height: 1px;
    width: 100%;
    margin: 12px 0;
}

.submit {
    cursor: pointer;
}

.submit:hover {
    color: rgb(36, 104, 242);
    text-decoration: underline;
}
</style>