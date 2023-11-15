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
                <el-button type="primary" size="mini" style="background-color: rgb(36,104,242);margin-right: 20px">
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
                <el-table-column width="150" prop="id" label="标签组ID"></el-table-column>
                <el-table-column width="200" prop="name" label="标签组名称"></el-table-column>
                <el-table-column width="250" prop="descript" label="标签组描述"></el-table-column>
                <el-table-column width="220" prop="startTime" label="创建时间"></el-table-column>
                <el-table-column width="220" prop="endTime" label="更新时间"></el-table-column>
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
                <el-form-item label="标签组名称" prop="labelgroupName">
                    <el-input placeholder="请输入标签组名称" v-model="editform.labelgroupName"></el-input>
                </el-form-item>
                <el-form-item label="标签组描述" prop="labelgroupDescript">
                    <el-input show-word-limit maxlength="100" placeholder="请输入标签组描述" type="textarea" v-model="editform.labelgroupDescript"></el-input>
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
    </div>
</template>
<script>
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
        let validatelabelgroupDescript = (rule, value, callback) => {
            if (value==="") {
                return callback(new Error('请输入标签组描述'));
            } else {
                callback()
            }
        };
        return {
            hideintroduction: false,
            labelGroup: [
                {
                    id: "1",
                    name: "1",
                    descript: "1",
                    startTime: "2023-11-05 19:31:26",
                    endTime: "2023-11-05 19:31:26",
                    label: ["鼠鼠", "哈哈哈", "耶比", "蛙入啊入啊"]
                },
                {
                    id: "2",
                    name: "2",
                    descript: "2",
                    startTime: "2023-11-05 19:31:26",
                    endTime: "2023-11-05 19:31:26",
                    label: ["鼠", "哈哈", "耶", "蛙入啊入"]
                },
                {
                    id: "3",
                    name: "3",
                    descript: "3",
                    startTime: "2023-11-05 19:31:26",
                    endTime: "2023-11-05 19:31:26",
                    label: ["鼠三", "哈哈", "比", "蛙啊入啊"]
                },
            ],
            inputvalue: "",
            delvisible: false,
            editvisible: false,
            chooserow: {},
            editform: { labelgroupName: "", labelgroupDescript: "" },
            editformrule: {
                labelgroupName: [
                    { required: true, validator: validatelabelgroupName, trigger: 'blur' }
                ],
                labelgroupDescript: [
                    { required: true, validator: validatelabelgroupDescript, trigger: 'blur' }
                ],
            }
        }
    },
    computed: {

    },
    methods: {
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
            let b=0
            this.labelGroup.map((item,index) => {
                if (item.id === a.id) {
                   b=index 
                }
            })
            this.labelGroup.slice(b)
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
            this.editform.labelgroupName = row.name
            this.editform.labelgroupDescript = row.descript
            this.editvisible=true
        },
        editok() {
            this.$refs.editform.validate((result) => {
                if (result) {
                    this.labelGroup.map(item => {
                        if (item.id === this.chooserow.id) {
                            item.name = this.editform.labelgroupName
                            item.descript =this.editform.labelgroupDescript
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
            this.editform.labelgroupName = ""
            this.editform.labelgroupDescript = ""
        },
        handleinput(row) {
            console.log(row);
            this.$router.push({path:"/LabelDetail",query:{group:JSON.stringify(row)}})
        }
    },
    mounted() {

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
</style>