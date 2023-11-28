<template>
    <div class="container">
        <div class="header">
            <span style="font-size: 16px;color: rgb(21,27,38);">标签组管理</span>
            <div style="display: flex;justify-content: space-between;">
                <span
                    style="font-size: 10px;color: rgb(21,27,38);">通过标签组管理功能可将多个常用标签创建为“标签组”进行统一管理，支持批量添加、修改、删除标签；创建成功后，在数据标注过程中可一键导入“标签组”，避免重复手动添加标签。</span>
                <span class="hide" @click="hide">
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
                        选择标签组可以往对应对应标签组里导入标签，点击新建标签组创建新的标签组
                    </span>
                </div>
            </div>
            <div class="teachbody">
                <div class="teachbodyitem">
                    <img style="width: 86px;height: 66px;" src="/label1.png">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            新建标签组
                        </div>
                        <div class="itemcontent">
                            点击“创建标签组”按钮，根据需要输入标签组名称和描述。
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 86px;height: 66px;" src="/label2.png">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            管理标签组
                        </div>
                        <div class="itemcontent">
                            支持手动或批量“添加/删除/修改”标签，您可上传csv、xls、txt格式文件批量添加标签。
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 86px;height: 66px;" src="/label3.png">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            调用标签组
                        </div>
                        <div class="itemcontent">
                            在线标注数据时，您可一键导入“标签组”，使用组内标签进行标注。
                        </div>
                    </div>
                </div>
            </div>
        </el-card>
        <el-card class="teachcard">
            <div slot="header" style="display: flex;justify-content: space-between;align-items:center">
                <el-button type="primary" size="mini" style="background-color: rgb(36,104,242);margin-right: 20px" @click="addvisible=true">
                    <i class="el-icon-plus"></i>&emsp;创建标签组
                </el-button>
                <div style="display: flex;justify-content: space-between;">
                    <el-input style="width: 80%;" size="small" v-model="inputvalue" placeholder="请输入标签组名称或ID"
                        suffix-icon="el-icon-search">
                    </el-input>
                    <el-button size="mini"><i class="el-icon-refresh" style="font-size: 15px;"></i></el-button>
                </div>
            </div>
            <el-table :data="labelGroup">
                <el-table-column width="350" prop="id" label="标签组ID"></el-table-column>
                <el-table-column width="350" prop="name" label="标签组名称"></el-table-column>
                <el-table-column label="操作">
                    <template slot-scope="scope">
                        <span class="tableplay" @click="handleinput(scope.row)">管理</span>
                        <span class="tableplay" @click="handlelook(scope.row)">编辑</span>
                        <span class="tableplay" @click="handleDelete(scope.row)">删除</span>
                    </template>
                </el-table-column>
            </el-table>
        </el-card>
        <el-dialog :visible.sync="editvisible" width="24%" top="15%" :destroy-on-close="true" :show-close="false"
            :close-on-click-modal="false">
            <span slot="title"><i class="el-icon-prompt"></i>编辑标签组</span>
            <el-form ref="editform" label-width="110px" label-position="left" :rules="editformrule" :model="editform">
                <el-form-item label="标签组名称" prop="name">
                    <el-input placeholder="请输入标签组名称" v-model="editform.name"></el-input>
                </el-form-item>
            </el-form>
            <span slot="footer" class="dialog-footer">
                <el-button size="mini" type="primary" @click="editok">确 定</el-button>
                <el-button size="mini" @click="editcancel">取 消</el-button>
            </span>
        </el-dialog>
        <el-dialog :visible.sync="delvisible" width="24%" top="15%" :destroy-on-close="true" :show-close="false"
            :close-on-click-modal="false">
            <span slot="title"><i class="el-icon-prompt"></i>确定删除该标签组吗？</span>
            <span style="font-size:14px;text-align:left;">删除后标签组下所有标签将被删除</span>
            <span slot="footer" class="dialog-footer">
                <el-button size="mini" type="primary" @click="delok">确 定</el-button>
                <el-button size="mini" @click="delcancel">取 消</el-button>
            </span>
        </el-dialog>
        <el-dialog title="新建标签组" :visible.sync="addvisible" width="24%" top="15%" :destroy-on-close="true"
            :show-close="false" :close-on-click-modal="false">
            <div><input placeholder="请输入标签组名" v-model="newgroup.labelName" class="inputlabel"></div>
            <div style="height: 160px;overflow-y: auto;">
                <div style="display: flex;justify-content: left;">
                    <span>序号</span>
                    <span style="margin-left: 15px;">标签名</span>
                </div>
                <div v-for="(item, index) in newgroup.labels" :key="index"
                    style="display: flex;justify-content: left;align-items: center;margin-top: 12px;">
                    <div style="font-size: 15px;margin-left: 8px;">
                        {{ index + 1 }}
                    </div>
                    <div class="labelblock">{{ item }}</div>
                    <i class="el-icon-close labelicon" @click="deletelabel(item)"></i>
                </div>
            </div>
            <i v-if="!addnewlabel" class="el-icon-circle-plus-outline labelicon" @click="addnewlabel = true"></i>
            <div v-else style="display: flex;flex-direction: column;justify-content: left;">
                <div style="display: flex;justify-content: left;align-items: center;">
                    <input placeholder="请输入新标签;不允许重复和空标签" v-model="newlabel" class="inputlabel">
                    <el-tooltip content="保存编辑" placement="top-start">
                        <i class="el-icon-check labelicon" @click="addsure"></i>
                    </el-tooltip>
                    <el-tooltip content="取消编辑" placement="top-end">
                        <i class="el-icon-close labelicon" @click="addcancel"></i>
                    </el-tooltip>
                </div>
                <span v-if="emptylabel" id="repeattext" class="animate__animated animate__shakeX">
                    {{ labelerror }}
                </span>
                <span v-else class="suretext" :class="{ addok: labelsure !== '待添加' }">
                    {{ labelsure }}
                </span>
            </div>
            <span slot="footer" class="dialog-footer">
                <el-button v-if="isupdate" size="mini" type="primary" @click="addgroup">创建</el-button>
                <el-button size="mini" @click="labelcancel">关闭</el-button>
            </span>
        </el-dialog>
    </div>
</template>
<script>
import axios from 'axios'
export default {
    name: "LabelManager",
    components: {

    },
    data() {
        let validatelabelgroupName = (rule, value, callback) => {
            if (value === '') {
                return callback(new Error('请输入标签组名称'));
            } else {
                callback()
            }
        };
        return {
            addvisible:false,
            hideintroduction: false,
            labelGroup: [
            ],
            newgroup: {
                labelName: "",
                labels:[]
            },
            inputvalue: "",
            delvisible: false,
            editvisible: false,
            chooserow: {},
            editform: { name: "" },
            editformrule: {
                name: [
                    { required: true, validator: validatelabelgroupName, trigger: 'blur' }
                ],
            },
            labelvisible: false,
            addnewlabel: false,
            emptylabel: false,
            labelerror: "",
            labelsure: "待添加",
            isupdate: false,
            newlabel:""
        }
    },
    computed: {

    },
    methods: {
        addgroup() {
            if (this.newgroup.labels.length === 0) {
                this.$message.error("请为标签组添加至少一条标签")
            } else if (this.newgroup.labelName ==="") {
                this.$message.error("请填写标签组名")
            } else {
                axios.post("http://192.168.224.150:10010/label", this.newgroup).then(res => {
                    if (res.data.code === 200) {
                        this.$message.success("创建成功")
                        this.getlabelgroup()
                        this.addvisible=false
                    }
                })
            }  
        },
        addsure() {
            if (this.newlabel === "") {
                this.labelerror = "标签不能为空"
                this.emptylabel = true
            } else if (this.newgroup.labels.includes(this.newlabel)) {
                this.labelerror = "标签重复"
                this.emptylabel = true
            } else {
                this.newgroup.labels.push(this.newlabel)
                this.labelsure = "添加成功"
                this.newlabel = ""
                this.emptylabel = false
                this.isupdate = true
            }
        },
        deletelabel(item) {
            this.newgroup.labels = this.newgroup.labels.filter(element => {
                return item !== element
            })
            this.isupdate = true
        },
        addcancel() {
            this.newlabel = ""
            this.addnewlabel = false
            this.addnewlabel = false
            this.emptylabel = false
            this.labelerror = ""
            this.labelsure = "待添加"

        },
        labelcancel() {
            this.addvisible = false
            this.addnewlabel = false
            this.emptylabel = false
            this.labelerror = ""
            this.labelsure = "待添加"
            this.newgroup.labels = []
            this.isupdate = false
        },
        hide() {
            this.hideintroduction = !this.hideintroduction
        },
        handleDelete(row) {
            console.log(row);
            this.chooserow = row
            this.delvisible = true
        },
        delok() {
            let a = { id: this.chooserow.id }
            axios.delete("http://192.168.224.150:10010/label/"+a.id).then(res => {
                if (res.data.code === 200) {
                    this.$message.success("删除成功")
                    this.getlabelgroup()
                } else {
                    this.$message.error("删除失败")
                }
            })
            /*发请求删除*/
            this.chooserow = {}
            this.delvisible = false
        },
        delcancel() {
            this.chooserow = {}
            this.delvisible = false
        },
        handlelook(row) {
            this.chooserow = row
            this.editform.labelId=row.id
            this.editvisible=true
        },
        editok() {
            this.$refs.editform.validate((result) => {
                if (result) {
                    console.log(this.editform);
                    axios.put("http://192.168.224.150:10010/label", this.editform).then(res => {
                        if (res.data.code === 200) {
                            this.$message.success("编辑成功")
                            this.getlabelgroup()
                        }
                    })
                    this.chooserow = {}
                    this.editvisible=false
                }
            })
        },
        editcancel() {
            this.chooserow = {}
            this.editvisible = false
            this.editform.name = ""
        },
        handleinput(row) {
            console.log(row);
            let a = {}
            a.id = row.id
            a.name = row.name
            console.log(row);
            this.$router.push({ path: "/LabelDetail", query: a  })
        },
        getlabelgroup() {
            axios.get("http://192.168.224.150:10010/label").then((res) => {
                console.log(res.data.data);
                this.labelGroup=res.data.data
            })
        }
    },
    mounted() {
        this.getlabelgroup()
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

.hide {
    font-size: 10px;
    color: #84868c;
    cursor: pointer;
}

.hide:hover {
    color: blue;
}

.box-card {
    width: 100%;
    height: 598px;
    margin-left: 1%;
}
.teachcard {
    text-align: left;
    margin: 10px;
}
/deep/.el-card__header {
    padding: 8px;
    padding-bottom: 0px;
}

.el-menu-item {
    padding: 0px;
    margin-left: 30px;
    font-size: 16px;
}
.el-menu--horizontal>.el-menu-item.is-active {
    border-bottom: 2px solid #409EFF;
    color: rgb(36, 104, 242);
}

/deep/.el-card__body {
    padding: 15px;
}
.listheaderitem {
    font-size: 14px;
    cursor: pointer;
    margin-right: 22px;
    color: #000;
    text-decoration: none;
    display: inline-flex;
    align-items: center;
}
.projectlist {
    margin-top: 15px
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

.tableplay {
    margin-left: 8px;
    color: rgb(26, 115, 232);
    font-size: 12px;
    cursor: pointer;
}

.tableplay:hover {
    color: rgb(82, 142, 255);
}

.labelblock {
    border: 1px solid rgb(221, 221, 221);
    display: flex;
    justify-content: left;
    align-items: center;
    height: 30px;
    width: 240px;
    padding-left: 5px;
    cursor: pointer;
    margin-left: 22px;
}

.labelblock:hover {
    border: 1px solid rgb(36, 104, 242);
}

.labelicon {
    margin-left: 12px;
    cursor: pointer;
    font-size: 25px;
}

.labelicon:hover {
    color: rgb(36, 104, 242);
}

.inputlabel {
    width: 308px;
    height: 28px;
    display: flex;
    justify-content: left;
    align-items: center;
    padding-left: 5px;
    border-radius: 0px;
    border: 1px solid rgb(221, 221, 221);
    outline-style: none;
    font-size: 14px;
}

.inputlabel:focus {
    border: 1px solid rgb(36, 104, 242);
}

@keyframes shake {
    0% {
        transform: translate(0, 0);
    }

    10% {
        transform: translate(-5px, -5px);
    }

    20% {
        transform: translate(5px, 5px);
    }

    30% {
        transform: translate(-5px, -5px);
    }

    40% {
        transform: translate(5px, 5px);
    }

    50% {
        transform: translate(-5px, -5px);
    }

    60% {
        transform: translate(5px, 5px);
    }

    70% {
        transform: translate(-5px, -5px);
    }

    80% {
        transform: translate(5px, 5px);
    }

    90% {
        transform: translate(-5px, -5px);
    }

    100% {
        transform: translate(0, 0);
    }
}

#repeattext {
    animation: shake 0.8s 1 forwards;
    color: red;
    font-size: 18px;
    text-align: left;
}

.suretext {
    color: rgb(192, 196, 204);
    font-size: 18px;
    text-align: left;
}

.addok {
    color: green;
}
</style>