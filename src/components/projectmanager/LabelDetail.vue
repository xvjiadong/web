<template>
    <div>
        <el-card>
            <div slot="header">
                <el-page-header @back="goBack" :content="labelgroup.name">
                </el-page-header>
            </div>
            <el-card>
                <div slot="header" style="display: flex;justify-content: space-between;align-items:center">
                    <div>
                        <el-button type="primary" size="mini" style="background-color: rgb(36,104,242);margin-right: 20px">
                            <i class="el-icon-plus"></i>&emsp;添加标签
                        </el-button>
                        <el-button :disabled="labelselect.length === 0" @click="delvisible = true" type="primary"
                            size="mini" style="background-color: rgb(36,104,242);margin-right: 20px">
                            <i class="el-icon-plus"></i>&emsp;批量删除标签
                        </el-button>
                    </div>
                </div>
                <el-table :key="refresh" :data="labelgroup.label" @selection-change="handleSelectionChange" :row-key="getrowkey">
                    <el-table-column type="selection" width="55" :reserve-selection="true"></el-table-column>
                    <el-table-column width="1200" prop="label" label="标签名称"></el-table-column>
                    <el-table-column label="操作">
                        <template slot-scope="scope">
                            <span class="tableplay" @click="handleinput(scope.row)">编辑</span>
                            <span class="tableplay" @click="handleDelete(scope.row)">删除</span>
                        </template>
                    </el-table-column>
                </el-table>
            </el-card>
            <el-dialog  :visible.sync="newvisible" width="24%" top="15%" :destroy-on-close="true" :show-close="false"
                :close-on-click-modal="false">
                <span slot="title"><i class="el-icon-prompt"></i>编辑标签</span>
                <el-form ref="newlabel" label-width="110px" label-position="left" :model="newlabel" :rules="newlabelrule" >
                    <el-form-item style="text-align: left;" label="标签名称">
                        <span>{{ selectlabel.label }}</span>
                    </el-form-item>
                    <el-form-item style="text-align: left;" label="新标签名称" prop="label">
                        <el-input size="mini" show-word-limit maxlength="100" placeholder="请输入标签新名称"
                            v-model="newlabel.label"></el-input>
                    </el-form-item>
                </el-form>
                <span slot="footer" class="dialog-footer">
                    <el-button size="mini" type="primary" @click="editok">确 定</el-button>
                    <el-button size="mini" @click="editcancel">取 消</el-button>
                </span>
            </el-dialog>
            <el-dialog :visible.sync="delvisible" width="24%" top="15%" :destroy-on-close="true" :show-close="false"
                :close-on-click-modal="false">
                <span slot="title"><i class="el-icon-prompt"></i>{{ selectlabel !== "" ? "确定删除该标签吗？" : "确定删除选中标签吗？"
                }}</span>
                <span style="font-size:14px;text-align:left;">删除后标签将不可恢复</span>
                <span slot="footer" class="dialog-footer">
                    <el-button size="mini" type="primary" @click="delok">确 定</el-button>
                    <el-button size="mini" @click="delcancel">取 消</el-button>
                </span>
            </el-dialog>
        </el-card>
    </div>
</template>
<script>
export default {
    name: "LabelDetail",
    components: {

    },
    data() {
        let validatelabel = (rule, value, callback) => {
            if (value === '') {
                return callback(new Error('请输入标签名称'));
            } else {
                let a = false
                this.labelgroup.label.map(item => {
                    if (item.label === value) {
                        a = true
                    }
                })
                if (!a) {
                    callback()
                } else {
                    return callback(new Error('标签名称重复'));
                }

            }
        };
        return {
            labelgroup: {},
            labelselect: [],
            delvisible: false,
            selectlabel: "",
            newvisible:false,
            newlabel: {
                label: ""
            },
            newlabelrule: {
                label: [
                    { required: true, validator: validatelabel, trigger: 'blur' }
                ]
            },
            refresh:false
        }
    },
    computed: {
    },
    methods: {
        goBack() {
            this.$router.push("/LabelManager")
        },
        handleSelectionChange(val) {
            this.labelselect = val
        },
        handleinput(row) {
            this.selectlabel = row
            this.newvisible=true
        },
        editok() {
            this.$refs.newlabel.validate(result => {
                if (result) {
                    let a = 0
                    this.labelgroup.label.map(item => {
                        if (item.label === this.selectlabel.label) {
                            a += 1
                            item.label = this.newlabel.label
                        }
                    })
                    if (a === 0) {
                        this.$message.Error("修改失败")
                    }
                    this.selectlable = ""
                    this.newlabel = {
                        label: ""
                    }
                    this.refresh=!this.refresh
                    this.newvisible = false
                }
            })
        },
        editcancel() {
            this.selectlable = ""
            this.newlabel = {
                label: ""
            }
            this.newvisible = false
        },
        handleDelete(row) {
            this.selectlabel = row
            this.delvisible = true
        },
        delok() {
            let a = { id: this.labelgroup.id, label: [] }
            if (this.selectlabel !== "") {
                a.label.push(this.selectlabel.label)
            } else {
                this.labelselect.map(item => {
                    a.label.push(item.label)
                })
            }
            this.labelgroup.label = this.labelgroup.label.filter(item => {
                return !a.label.includes(item.label)
            })
            /*发请求删除*/
            this.selectlabel = ""
            this.labelselect = []
            this.delvisible = false
        },
        delcancel() {

            this.delvisible = false
        },
        getrowkey(row) {
            return row.label
        }
    },
    mounted() {
        this.labelgroup = JSON.parse(this.$route.query.group);
        this.labelgroup.label.map((item, index) => {
            let a = item
            this.labelgroup.label[index] = { label: a }
        })
        console.log(this.labelgroup);
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
</style>