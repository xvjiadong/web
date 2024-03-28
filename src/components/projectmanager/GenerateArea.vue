<template>
    <div>
        <el-select @change="changeversion" filterable v-model="data_get.version" placeholder="请选择需增强的版本" size="small">
            <el-option v-for="item in task" :key="item.versionId" :value="item.versionId"
                :label="`${item.taskName}-${item.callType}`">
            </el-option>
        </el-select>
        <el-card v-if="data_get.version !== ''" style="margin: 15px;">
            <div slot="header" style="display: flex;justify-content: space-between;">
                <span>筛选图片，点击提交按钮，未选择的图片将删除</span>
                <div style="display: flex;justify-content: space-around;align-items: center;">
                    <el-tooltip placement="top-start" content="点击分批次筛选图片">
                        <i class=el-icon-s-marketing :class="{ 'currenttype': type == 0 }"
                            style="font-size: 25px;cursor: pointer;"></i>
                    </el-tooltip>
                    <el-tooltip placement="top-start" content="点击一次性筛选图片">
                        <i class="el-icon-s-grid" :class="{ 'currenttype': type == 1 }"
                            style="font-size: 25px;cursor: pointer;"></i>
                    </el-tooltip>
                    <el-button @click="submit" type="primary" size="small">提交</el-button>
                </div>
            </div>
            <div v-if="piclist.length > 0">
                <el-checkbox-group @change="handleCheckedCitiesChange" v-model="data_submit.need">
                    <el-checkbox :label="image.id" v-for="image in piclist" :key="image.ossPath + '-' + image.id">
                        <img :src="image.ossPath" class="generate_pic">
                    </el-checkbox>
                </el-checkbox-group>
                <el-pagination v-if="piclist.length !== 0" :hide-on-single-page="true" :current-page="data_get.current"
                    :page-sizes="[10]" :page-size="10" background layout="sizes, prev, pager, next, jumper"
                    :page-count="pages" @current-change="handleCurrentChange" />
            </div>
            <el-empty v-else description="未生成过图片"></el-empty>
        </el-card>
    </div>
</template>

<script>
import axios from 'axios'
export default {
    data() {
        return {
            type: 0,
            task: [],
            piclist: [],
            data_get: {
                current: 1,
                pageSize: 10,
                version: ''
            },
            data_submit: {
                need: [],
                noNeed: []
            },
            pages: 0
        }
    },
    methods: {
        submit() {
            axios.post("http://120.26.142.114:10010/dataset/create/temp", this.data_submit)
                .then(res => {
                    console.log(res.data);
                    if (res.data.code === 200) {
                        if (this.data_get.current != 1) {
                            this.data_get.current -= 1
                        }
                        this.getdata_split()
                    }

                }).catch(e => {
                    console.log(e);
                })
        },
        handleCheckedCitiesChange(val) {
            this.data_submit.noNeed = this.data_submit.noNeed.filter(item => {
                return val.findIndex(item2 => item2 == item) == -1
            })
        },
        handleCurrentChange(val) {
            this.data_get.current = val
            this.getdata_split()
        },
        changeversion(val) {
            this.data_get.version = val
            this.getdata_split()
        },
        getdata_all() {

        },
        getdata_split() {
            axios.post('http://120.26.142.114:10010/dataset/create', this.data_get)
                .then(res => {
                    if (res.data.code === 200) {
                        this.piclist = res.data.data.records
                        this.piclist.forEach(item => {
                            this.data_submit.noNeed.push(item.id)
                        })
                        this.pages = res.data.data.pages
                    }
                })
                .catch(e => {
                    console.log(e);
                })
        },
        getversion() {
            axios.get("http://120.26.142.114:10010/items/version").then(res => {
                this.task = res.data.data.filter(item => {
                    return item.callType === '图像文本标注' || item.callType.includes("图片分类标注") || item.callType === "分割标注" || item.callType === "物体检测" || item.callType === "线标注" || item.callType === "点标注"
                })
            })
        },
    },
    mounted() {
        this.getversion()
    }
}
</script>

<style scoped>
.currenttype {
    color: rgb(36, 104, 242);
}

.generate_pic {
    width: 210px;
    height: 210px;
    float: left;
}

/deep/.el-checkbox {
    color: #606266;
    font-weight: 500;
    font-size: 14px;
    cursor: pointer;
    -webkit-user-select: none;
    -moz-user-select: none;
    user-select: none;
    margin-left: 10px;
    margin-top: 10px;
    margin-right: 0;
}
</style>