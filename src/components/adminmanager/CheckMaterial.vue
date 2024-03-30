<template>
    <div :style="mainbody">
        <div :style="leftbody">
            <el-table :data="companylist">
                <el-table-column prop="companyName" label="公司名称"></el-table-column>
                <el-table-column prop="position" label="负责人职位"></el-table-column>
                <el-table-column prop="teamSize" label="团队规模"></el-table-column>
                <el-table-column prop="phoneNumber" label="联系电话"></el-table-column>
                <el-table-column>
                    <template slot-scope="scope">
                        <el-tooltip placement="left">
                            <div slot="content">
                                点击查看详细申请材料
                            </div>
                            <i @click="change(scope.$index)" style="cursor: pointer;" class="el-icon-info"></i>
                        </el-tooltip>
                        <span style="cursor: pointer;color: rgb(36,104,242);margin-left: 15px;"
                            @click="accept(scope.row)">通过</span>
                        <el-popover placement="bottom" title="打回原因" width="200" trigger="click">
                            <el-input v-model="refuseform.refuseReason" placeholder="请填写拒绝原因" size="small"></el-input>
                            <div style="display: flex;justify-content: space-around;">
                                <el-button type="primary" size="small" @click="refuseok">确定</el-button>
                                <el-button size="small" @click="refusecancel">取消</el-button>
                            </div>
                            <span slot="reference" style="cursor: pointer;color: rgb(36,104,242);margin-left: 15px;"
                                @click="refuse(scope.row)">打回</span>
                        </el-popover>

                    </template>
                </el-table-column>
            </el-table>
            <el-pagination v-if="companylist.length !== 0" :hide-on-single-page="true" :current-page="page"
                :page-sizes="[5]" :page-size="5" background layout="sizes, prev, pager, next, jumper" :total="total"
                @current-change="handleCurrentChange" />
        </div>
        <div :style="centerbody">
            <i @click="change(-1)" class="el-icon-d-arrow-left"
                style="font-size: 45px;color: rgb(36,104,242);cursor: pointer;border-radius: 50%;box-shadow: 0px 0px 5px 3px rgba(0, 0, 0, 0.2);"></i>
        </div>
        <div :style="rightbody">
            <div v-if="chooseindex != -1">
                <el-form>
                    <el-form-item label="入驻理由">
                        {{ companylist[chooseindex].reason }}
                    </el-form-item>
                    <el-form-item label="申请材料">
                        <img style="width:230px;height:230px" :src="item.data" v-for="(item) in detail"
                            :key="item.data">
                    </el-form-item>
                </el-form>
            </div>
            <div v-else>
                <el-empty description="请选择具体公司已查看提交材料"></el-empty>
            </div>
        </div>
    </div>
</template>
<script>
import axios from 'axios'
export default {
    data() {
        return {
            page: 1,
            total: 0,
            chooseindex: -1,
            refusevis: false,
            refuseform: {
                refuseReason: "",
                id: ''
            },
            companylist: [

            ],
            detail: [],
            mainbody: {
                width: '100%',
                height: '100%',
                display: 'flex',
                justifyContent: 'space-around',
                overflowX: 'hidden',
            },
            leftbody: {
                width: '90%',
                height: '90%',
                transition: 'all 1s'
            },
            rightbody: {
                height: '90%',
                width: '0',
                overflowX: 'hidden',
                transition: 'all 1s'
            },
            centerbody: {
                height: '90%',
                width: '5%',
                display: 'flex',
                alignItems: 'center',
                transform: "rotateY(0deg)",
                transition: 'all 1s'
            }
        }
    },
    methods: {
        handleCurrentChange(val) {
            this.get_sample_data(val)
        },
        refuseok() {
            //发请求
            axios.get(`http://120.26.142.114:10010/users/company/noPass?id=${this.refuseform.id}&no_passed=${this.refuseform.refuseReason}`)
                .then(res => {
                    if (res.data.code === 200) {
                        this.$message.success("审核成功")
                        this.refusecancel()
                        this.get_sample_data(this.page)
                    }
                })
                .catch(e => {
                    console.log(e);
                })
        },
        refusecancel() {
            this.refusevis = false
            this.refuseform = {
                refuseReason: "",
                id: ''
            }
        },
        change(appear) {
            if (appear !== -1) {
                this.chooseindex = appear
                this.centerbody.transform = 'rotateY(180deg)'
                this.leftbody.width = '50%'
                this.rightbody.width = '50%'
                this.get_detail(this.companylist[appear].id)
                return
            }
            this.centerbody.transform = this.centerbody.transform == 'rotateY(0deg)' ? 'rotateY(180deg)' : 'rotateY(0deg)'
            this.leftbody.width = this.centerbody.transform == 'rotateY(0deg)' ? '90%' : '50%'
            this.rightbody.width = this.centerbody.transform == 'rotateY(0deg)' ? '0%' : '50%'
            setTimeout(() => {
                if (this.rightbody.width === '0%') {
                    this.chooseindex = -1
                    this.detail = []
                }
            }, 800)
        },
        accept(item) {
            axios.get("http://120.26.142.114:10010/users/company/pass?id=" + item.id)
                .then(res => {
                    if (res.data.code === 200) {
                        this.$message.success("审核成功")
                        this.get_sample_data(this.page)
                    }
                }).catch(e => {
                    console.log(e);
                })
        },
        refuse(item) {
            this.refuseform.id = item.id
        },
        get_sample_data(page) {
            axios.post("http://120.26.142.114:10010/users/company/get", { current: page, pageSize: 5 })
                .then(res => {
                    if (res.data.code === 200) {
                        this.companylist = res.data.data.records
                        this.total = res.data.data.total
                    }
                })
        },
        get_detail(id) {
            axios.get("http://120.26.142.114:10010/users/company/get/data?id=" + id)
                .then(res => {
                    if (res.data.code === 200) {
                        this.detail = res.data.data
                    }
                })
        },
    },
    mounted() {
        this.get_sample_data(this.page)
    }
}
</script>

<style scoped>
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