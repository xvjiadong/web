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
        </div>
        <div :style="centerbody">
            <i @click="change(-1)" class="el-icon-d-arrow-left"
                style="font-size: 45px;color: rgb(36,104,242);cursor: pointer;border-radius: 50%;box-shadow: 0px 0px 5px 3px rgba(0, 0, 0, 0.2);"></i>
        </div>
        <div :style="rightbody">
            <div v-if="chooseindex != -1">
                <el-form>
                    <el-form-item label="入驻理由">
                        {{ detail.reason }}
                    </el-form-item>
                    <el-form-item label="申请材料">
                        <img :src="item" v-for="(item, index) in detail.piclist" :key="item + '-' + index">
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
//import axios from 'axios'
export default {
    data() {
        return {
            page: 1,
            total: 0,
            chooseindex: -1,
            refusevis: false,
            refuseform: {
                refuseReason: "",
                companyNumber: ''
            },
            companylist: [
                {
                    companyName: "dasads",
                    position: "asdda",
                    teamSize: "asdasd",
                    phoneNumber: "re",
                    companyNumber: "tre",
                    piclist: ['https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg'],
                    reason: "48984",
                    vis: false
                },
                {
                    companyName: "dasads",
                    position: "asdda",
                    teamSize: "asdasd",
                    phoneNumber: "re",
                    companyNumber: "ttgdre",
                    piclist: ['https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-04/5474de4e0e224fedb38fd7bfb8e656b9-新ocr/V1/1.jpg'],
                    reason: "jgh"
                },
                {
                    companyName: "dasads",
                    position: "asdda",
                    teamSize: "asdasd",
                    phoneNumber: "re",
                    companyNumber: "tre",
                    piclist: ['https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg'],
                    reason: "jgh"
                },
                {
                    companyName: "dasads",
                    position: "asdda",
                    teamSize: "asdasd",
                    phoneNumber: "re",
                    companyNumber: "tre",
                    piclist: ['https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg'],
                    reason: "jgh"
                },
                {
                    companyName: "dasads",
                    position: "asdda",
                    teamSize: "asdasd",
                    phoneNumber: "re",
                    companyNumber: "tre",
                    piclist: ['https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg'],
                    reason: "jgh"
                },
                {
                    companyName: "dasads",
                    position: "asdda",
                    teamSize: "asdasd",
                    phoneNumber: "re",
                    companyNumber: "tre",
                    piclist: ['https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg'],
                    reason: "jgh"
                },
                {
                    companyName: "dasads",
                    position: "asdda",
                    teamSize: "asdasd",
                    phoneNumber: "re",
                    companyNumber: "tre",
                    piclist: ['https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg', 'https://items-storage.oss-cn-beijing.aliyuncs.com/datasets/2024-03-03/f28738c4a0514e2a9c6ea45c6b03aee0-GroundingDINO/V2/objects365_v2_00914816.jpg'],
                    reason: "jgh"
                },
            ],
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
    computed: {
        detail() {
            if (this.chooseindex == -1) {
                return ""
            }
            return { piclist: this.companylist[this.chooseindex].piclist, reason: this.companylist[this.chooseindex].reason }
        }
    },
    methods: {
        refuseok() {
            //发请求
        },
        refusecancel() {
            this.refuseform = {
                refuseReason: "",
                companyNumber: ''
            }
        },
        change(appear) {
            if (appear !== -1) {
                this.chooseindex = appear
                this.centerbody.transform = 'rotateY(180deg)'
                this.leftbody.width = '50%'
                this.rightbody.width = '50%'
                return
            }
            this.centerbody.transform = this.centerbody.transform == 'rotateY(0deg)' ? 'rotateY(180deg)' : 'rotateY(0deg)'
            this.leftbody.width = this.centerbody.transform == 'rotateY(0deg)' ? '90%' : '50%'
            this.rightbody.width = this.centerbody.transform == 'rotateY(0deg)' ? '0%' : '50%'
        },
        accpet(item) {
            console.log(item);
        },
        refuse(item) {
            this.refuseform.companyNumber = item.companyNumber
            this.refusevis = true
        },
    },
    mounted() {
        /*axios.get("")
            .then(res => {
                console.log(res);
            })
            .catch(e => {
                console.log(e);
            })*/
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