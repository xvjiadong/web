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
                        <el-button type="primary" size="mini" style="background-color: rgb(36,104,242);margin-right: 20px"
                            @click="add">
                            <i class="el-icon-plus"></i>&emsp;添加标签
                        </el-button>
                        <el-button :disabled="labelselect.length === 0" @click="delvisible = true" type="primary"
                            size="mini" style="background-color: rgb(36,104,242);margin-right: 20px">
                            <i class="el-icon-plus"></i>&emsp;批量删除标签
                        </el-button>
                    </div>
                </div>
                <el-table :key="refresh" :data="labelgroup.label" @selection-change="handleSelectionChange"
                    :row-key="getrowkey">
                    <el-table-column type="selection" width="55" :reserve-selection="true"></el-table-column>
                    <el-table-column width="400" prop="id" label="标签ID"></el-table-column>
                    <el-table-column width="400" prop="labels" label="标签名称"></el-table-column>
                    <el-table-column width="400" label="操作">
                        <template slot-scope="scope">
                            <span class="tableplay" @click="handleinput(scope.row)">编辑</span>
                            <span class="tableplay" @click="handleDelete(scope.row)">删除</span>
                        </template>
                    </el-table-column>
                </el-table>
            </el-card>
            <el-dialog :visible.sync="newvisible" width="24%" top="15%" :destroy-on-close="true" :show-close="false"
                :close-on-click-modal="false">
                <span slot="title"><i class="el-icon-prompt"></i>编辑标签</span>
                <el-form ref="newlabel" label-width="110px" label-position="left" :model="newlabel" :rules="newlabelrule">
                    <el-form-item style="text-align: left;" label="标签名称">
                        <span>{{ selectlabel.labels }}</span>
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
            <el-dialog title="新增标签" :visible.sync="addvisible" width="24%" top="15%" :destroy-on-close="true"
                :show-close="false" :close-on-click-modal="false">
                <el-input v-model="addlabel" placeholder="请输入新标签"></el-input>
                <el-button size="mini" type="primary" @click="addok">确 定</el-button>
                <el-button size="mini" @click="addcancel">取 消</el-button>
            </el-dialog>
        </el-card>
    </div>
</template>
<script>
import axios from 'axios'
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
                    if (item.labels === value) {
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
            newvisible: false,
            newlabel: {
                label: ""
            },
            newlabelrule: {
                label: [
                    { required: true, validator: validatelabel, trigger: 'blur' }
                ]
            },
            refresh: false,
            addvisible: false,
            addlabel: ""
        }
    },
    computed: {
    },
    methods: {
        goBack() {
            this.$router.push("/LabelManager")
        },
        handleSelectionChange(val) {
            val.map(item => {
                this.labelselect.push(item.labels)
            })
        },
        handleinput(row) {
            this.selectlabel = row
            this.newvisible = true
        },
        addok() {
            if (this.addlabel === "") {
                this.$message.error("标签名称不能为空")
                return
            }
            let isavail = false
            this.labelgroup.label.map(item => {
                if (item.labels === this.addlabel) {
                    isavail = true
                }
            })
            if (!isavail) {
                let a = { labelId: "", labels: [] }
                this.labelgroup.label.map(item => {
                    a.labels.push(item.labels)
                })
                a.labelId = this.labelgroup.id
                a.labels.push(this.addlabel)
                axios.put("http://120.26.142.114:10010/label/group", a).then(res => {
                    if (res.data.code === 200) {
                        this.addvisible = false
                        this.addlabel=""
                        this.getlabel()
                    } else {
                        this.$message.error("添加失败")
                    }
                })
            } else {
                this.$message.error("标签名称重复")
            }
        },
        addcancel() {
            this.addlabel = ""
            this.addvisible = false
        },
        add() {
            this.addvisible = true
        },
        editok() {
            this.$refs.newlabel.validate(result => {
                if (result) {
                    this.labelgroup.label.map(item => {
                        if (item.labels === this.selectlabel.labels) {
                            item.labels = this.newlabel.label
                        }
                    })
                    let a = { labelId: "", labels: [] }
                    this.labelgroup.label.map(item => {
                        a.labels.push(item.labels)
                    })
                    a.labelId = this.labelgroup.id
                    axios.put("http://120.26.142.114:10010/label/group", a).then(res => {
                        if (res.data.code === 200) {
                            this.getlabel()
                        }
                    })
                    this.selectlable = ""
                    this.newlabel = { label: "" }
                    this.refresh = !this.refresh
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
            let a = { labelId: this.labelgroup.id, labels: [] }
            if (this.selectlabel !== "") {
                a.labels.push(this.selectlabel.labels)
            } else {
                this.labelselect.map(item => {
                    a.labels.push(item.labels)
                })
            }
            let b = []
            this.labelgroup.label.map(item => {
                if (!a.labels.includes(item.labels)) {
                    b.push(item.labels)
                }
            })
            a.labels = b
            console.log(a);
            axios.put("http://120.26.142.114:10010/label/group", a).then(res => {
                console.log(res.data);
                if (res.data.code === 200) {
                    this.getlabel()
                }
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
            return row.labels
        },
        getlabel() {
            console.log(this.labelgroup.id);
            axios.get("http://120.26.142.114:10010/label/group/" + this.labelgroup.id).then(res => {
                this.labelgroup.label = res.data.data
                this.refresh = !this.refresh
            })
        }
    },
    mounted() {
        this.labelgroup.id = this.$route.query.id
        this.getlabel()
        this.labelgroup.name = this.$route.query.name
        /*this.labelgroup.label.map((item, index) => {
            let a = item
            this.labelgroup.label[index] = { label: a }
        })*/
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