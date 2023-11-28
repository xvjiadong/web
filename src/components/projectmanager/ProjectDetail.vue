<template>
    <div>
        <el-card>
            <div slot="header">
                <el-page-header @back="goBack" :content="project.name">
                </el-page-header>
            </div>
            <el-card class="teachcard">
                <div>
                    <div class="projectlist">
                        <el-card>
                            <div slot="header" style="display: flex;justify-content: space-between;align-items: center;">
                                <div>
                                    <span style="font-size: 12px;color: rgb(21,27,38);">{{ project.name }}</span>&emsp;
                                    <span style="font-size: 12px;color: rgb(21,27,38);">项目ID：{{ project.id }}</span>
                                </div>
                                <div>
                                    <span class="listheaderitem" @click="add">
                                        <img style="width: 14px;height: 14px;" src="/add.svg">
                                        <span style="font-size: 12px;margin-left: 3px;">新增版本</span>
                                    </span>
                                    <span class="listheaderitem" @click="del">
                                        <i style="font-size: 16px;" class="el-icon-delete"></i>
                                        <span style="font-size: 12px;margin-left: 3px;">删除</span>
                                    </span>
                                </div>
                            </div>
                            <el-table ref="project" :data="showtablelist" @selection-change="handleSelectionChange"
                                :row-key="getrowkey">
                                <el-table-column type="selection" width="55" :reserve-selection="true"></el-table-column>
                                <el-table-column type="expand" width="55" label="任务">
                                    <template slot-scope="scope">
                                        <div style="text-align:center" v-if="scope.row.userVOList">
                                            <el-table :data="scope.row.userVOList">
                                                <el-table-column prop="dataNumber" label="任务数量"></el-table-column>
                                                <el-table-column prop="userId" label="任务承办人"></el-table-column>
                                                <el-table-column prop="startTime" label="创建时间"></el-table-column>
                                                <el-table-column prop="endTime" label="截止时间"></el-table-column>
                                                <el-table-column label="数据类型">
                                                    <template slot-scope="scope">
                                                        <span @click="a(scope)">{{ project.dataType }}</span>
                                                    </template>
                                                </el-table-column>
                                                <el-table-column prop="personalProgress" label="任务进度"></el-table-column>
                                                <el-table-column label="操作">
                                                    <template slot-scope="scope">
                                                        <el-button size="mini"
                                                            @click="handleEdit(scope.$index, scope.row)">查看</el-button>
                                                    </template>
                                                </el-table-column>
                                            </el-table>
                                        </div>
                                        <div style="text-align:center" v-else>
                                            <span>未分配任务</span>
                                        </div>
                                    </template>
                                </el-table-column>
                                <el-table-column prop="verName" label="版本"></el-table-column>
                                <el-table-column prop="dataNumber" label="数据量"></el-table-column>
                                <el-table-column label="数据类型">
                                    <template slot-scope="scope">
                                        <span @click="a(scope)">{{ project.dataType }}</span>
                                    </template>
                                </el-table-column>
                                <el-table-column prop="callType" label="标注类型"></el-table-column>
                                <el-table-column prop="progress" label="标注进度"></el-table-column>
                                <el-table-column label="操作">
                                    <template slot-scope="scope">
                                        <span class="tableplay" @click="handleinput(scope.row)">导入</span>
                                        <span class="tableplay" @click="handlelook(scope.row)">查看</span>
                                        <span class="tableplay" @click="handleSchedule(scope.row)">调度</span>
                                        <span class="tableplay" @click="handleDelete(scope.row)">删除</span>
                                        <span class="tableplay" @click="handleoutput(scope.row)"
                                            v-if="scope.row.markprocess === '100%'">导出</span>
                                    </template>
                                </el-table-column>
                            </el-table>
                        </el-card>
                    </div>
                </div>
            </el-card>
            <!--<el-pagination v-if="project.versions.length !== 0" :current-page="currentPage" :page-sizes="[2, 4, 6, 8]"
                :page-size="pageSize" background layout="sizes, prev, pager, next, jumper" :total="project.versions.length"
                @current-change="handleCurrentChange" @size-change="handleSizeChange" />-->
        </el-card>
        <el-dialog title="新增项目版本" :visible.sync="centerDialogVisible" width="40%" :center="false" :destroy-on-close="true">
            <el-form ref="add" :model="addnewversion" label-width="110px" class="form" label-position="left">
                <el-form-item label="数据集版本" v-model="addnewversion.versionname" class="formitem">
                    {{ addnewversion.versionname }}
                </el-form-item>
                <el-form-item label="备注信息" class="formitem">
                    <el-input rows="4" size="mini" resize="none" show-word-limit v-model="addnewversion.descript"
                        type="textarea" maxlength="50" placeholder="请备注本次版本主要做的修改，如添加数据、更换标注方式等，限制50个字符内"></el-input>
                </el-form-item>
                <el-form-item label="继承历史版本" class="formitem">
                    <el-switch :width="45" v-model="isextends" active-color="rgb(36,104,242)"
                        inactive-color="rgb(234,46,46)" :active-value="true" :inactive-value="false" active-text="继承"
                        inactive-text="不继承">
                    </el-switch>
                </el-form-item>
                <el-form-item v-if="isextends" label="历史版本" class="formitem">
                    <el-select size="mini" v-model="addnewversion.marktype" placeholder="请选择历史版本">
                        <el-option v-for="item in project.versions" :key="item.verName" :value="item.callType"
                            :label="`${item.verName}-${item.callType}`"></el-option>
                    </el-select>
                </el-form-item>
                <el-form-item v-else label="标注类型" v-model="addnewversion.marktype" class="formitem">
                    <el-select size="mini" v-model="addnewversion.marktype" placeholder="请选择标注类型">
                        <el-option v-for="item in marktypelist" :key="item.value" :value="item.value"
                            :label="item.value"></el-option>
                    </el-select>
                </el-form-item>
            </el-form>
            <span slot="footer" class="dialog-footer">
                <el-button size="mini" type="primary" @click="addok">确 定</el-button>
                <el-button size="mini" @click="addcancel">取 消</el-button>
            </span>
        </el-dialog>
        <el-dialog title="删除数据集" :visible.sync="delvisible" width="24%" top="15%" :destroy-on-close="true">
            <span style="font-size:14px;text-align:left;">{{ deldialogcontent }}</span>
            <span slot="footer" class="dialog-footer">
                <el-button size="mini" type="primary" @click="delvisible = false">确 定</el-button>
                <el-button size="mini" @click="delvisible = false">取 消</el-button>
            </span>
        </el-dialog>
    </div>
</template>
<script>
import axios from 'axios'
export default {
    name: "ProjectDetail",
    components: {

    },
    data() {
        return {
            project: {
                projectid: "188865667",     //项目id
                name: "测试数据1",          //项目名
                datatype: "图像",          //数据类型
                version: [                 //下辖版本
                    {
                        versionid: "1697286",      //版本id
                        versionname: "v1",         //版本号
                        versionnumber: "600",      //数据量
                        marktype: "图片分类",      //标注任务类型
                        markprocess: "100%",        //标注进度
                        task: [               //任务
                            {
                                taskid: "1",       //任务id
                                tasknumber: "150",   //任务标注数量
                                taskperson: "测试标注员1",   //任务承担人
                                taskprocess: "15%",  //任务进度
                                taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                juideprocess: "0%",     //审核进度
                            },
                            {
                                taskid: "2",       //任务id
                                tasknumber: "150",   //任务标注数量
                                taskperson: "测试标注员2",   //任务承担人
                                taskprocess: "12%",  //任务进度
                                taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                juideprocess: "0%",     //审核进度
                            },
                            {
                                taskid: "3",       //任务id
                                tasknumber: "150",   //任务标注数量
                                taskperson: "测试标注员3",   //任务承担人
                                taskprocess: "42%",  //任务进度
                                taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                juideprocess: "0%",     //审核进度
                            },
                            {
                                taskid: "4",       //任务id
                                tasknumber: "150",   //任务标注数量
                                taskperson: "测试标注员4",   //任务承担人
                                taskprocess: "56%",  //任务进度
                                taskcreatetime: "2023-11-05 10:47",   //任务创建时间
                                taskdeadline: "2023-11-15 10:47",     //任务截止时间
                                juideprocess: "0%",     //审核进度
                            }
                        ]
                    },
                    {
                        versionid: "1592156",
                        versionname: "v2",
                        versionnumber: "452",
                        datatype: "图像",
                        marktype: "图像文本识别",
                        markprocess: "15%",

                    },
                    {
                        versionid: "15456",
                        versionname: "v3",
                        versionnumber: "452",
                        datatype: "图像",
                        marktype: "图像文本识别",
                        markprocess: "15%",

                    },
                    {
                        versionid: "1uyjh6",
                        versionname: "v4",
                        versionnumber: "452",
                        datatype: "图像",
                        marktype: "图像文本识别",
                        markprocess: "15%",

                    },
                    {
                        versionid: "vtvgh156",
                        versionname: "v5",
                        versionnumber: "452",
                        datatype: "图像",
                        marktype: "图像文本识别",
                        markprocess: "15%",

                    },
                    {
                        versionid: "1ijk156",
                        versionname: "v6",
                        versionnumber: "452",
                        datatype: "图像",
                        marktype: "图像文本识别",
                        markprocess: "15%",

                    },
                    {
                        versionid: "15fhf",
                        versionname: "v7",
                        versionnumber: "452",
                        datatype: "图像",
                        marktype: "图像文本识别",
                        markprocess: "15%",

                    },
                    {
                        versionid: "1derdg6",
                        versionname: "v8",
                        versionnumber: "452",
                        datatype: "图像",
                        marktype: "图像文本识别",
                        markprocess: "15%",

                    },
                    {
                        versionid: "gjb56",
                        versionname: "v9",
                        versionnumber: "452",
                        datatype: "图像",
                        marktype: "图像文本识别",
                        markprocess: "15%",

                    },
                    {
                        versionid: "yhgn156",
                        versionname: "v10",
                        versionnumber: "452",
                        datatype: "图像",
                        marktype: "图像文本识别",
                        markprocess: "15%",

                    }
                ]
            },
            currentPage: 1,
            pageSize: 4,
            delvisible: false,
            centerDialogVisible: false,
            multipleSelection: [],
            choose: [],
            selectrow: [],
            addnewversion: {
                versionname: "",
                descript: "",
                marktype: ""
            },
            isextends: true,
        }
    },
    computed: {
        showtablelist() {
            return this.project.versions
        },
        marktypelist() {
            let a = [{ value: "图像分类", label: "图像分类" }, { value: "多边形标注", label: "多边形标注" }, { value: "文本检测", label: "文本检测" }, { value: "点标注", label: "点标注" }, { value: "线标注", label: "线标注" }, { value: "混合标注", label: "混合标注" }]
            let b = [{ value: "关系抽取", label: "关系抽取" }, { value: "证据划选", label: "证据划选" }, { value: "实体抽取", label: "实体抽取" }, { value: "混合标注", label: "混合标注" }]
            if (this.project.dataType === "图像") {
                return a
            } else if (this.project.dataType === "文本") {
                return b
            }
            return []
        },
        deldialogcontent() {
            console.log(this.multipleSelection.length, this.project.versions.length);
            if (!this.delvisible) {
                return ""
            }
            if (this.selectrow.length > 0) {
                return "操作删除后，该项目版本及所归属的任务都将会被删除且不可恢复，确认要删除吗？"
            }
            if (this.multipleSelection.length === this.project.versions.length) {
                return "操作删除后，项目及全部版本数据都将会被删除且不可恢复，确认要删除吗？"
            } else if (this.multipleSelection.length === 0) {
                return "请选择项目版本进行删除"
            }
            return "操作删除后，该项目版本及所归属的任务都将会被删除且不可恢复，确认要删除吗？"
        }
    },
    methods: {
        getproject() {
            axios.get("http://192.168.224.150:10010/items").then((res) => {
                this.project = res.data.data;
                console.log(this.project);                
            })
        },
        goBack() {
            this.$router.push("/ProjectList")
        },
        addcancel() {
            this.centerDialogVisible = false
            this.isextends = true
            this.addnewversion = {
                versionname: "",
                descript: "",
                marktype: ""
            }
        },
        addok() {
            if (this.addnewversion.marktype) {
                this.addnewversion.id = this.project.id
                let a = {}
                a.id = this.addnewversion.projectid
                a.markType = this.addnewversion.marktype
                a.verAttributes = this.addnewversion.descript
                a.version = this.addnewversion.versionname
                axios.post("http://192.168.224.150:10010/items/version/add", a).then(res => {
                    console.log(res.data);
                })
                this.refresh()
                this.$nextTick(() => {
                    this.centerDialogVisible = false
                    this.isextends = true
                    this.addnewversion = {
                        versionname: "",
                        descript: "",
                        marktype: ""
                    }
                })
            } else {
                this.$message({ type: "error", message: "请选择标注类型" })
            }
        },
        add() {
            let a = -1;
            this.project.versions.forEach(element => {
                let b = parseInt(element.verName.substring(1))
                a = b > a ? b : a
            });
            this.addnewversion.versionname = "V" + (a + 1)
            this.$nextTick(() => {
                this.centerDialogVisible = true
            })
        },
        delok() {
            let form
            if (this.selectrow.length > 0) {
                let a = []
                this.selectrow.map(item => {
                    a.push(item.verName)
                })
                form = { id: this.chooseitem.id, versionId: a }
            } else {
                if (this.multipleSelection.length === this.project.versions.length) {
                    form = { tid: this.project.id }
                } else if (this.multipleSelection.length === 0) {
                    this.delcancel()
                    return
                }
                else {
                    form = { id: this.project.id, versionId: this.multipleSelection }
                }
            }
            axios.post('http://192.168.224.150:10010/items/delete', form).then((res) => {
                if (res.data.code === 200) {
                    this.$message({ type: "success", message: "删除完毕" })
                    this.chooseitem=""
                    this.multipleSelection = []
                    this.selectrow=[]
                    this.$nextTick(()=>{
                        this.getproject()
                    })
                    this.delvisible=false
                } else {
                    this.$message({ type: "error", message: "删除失败" })
                    this.delvisible=false
                }
            })
        },
        delcancel() {
            this.multipleSelection = this.$refs.project.selection
            this.delvisible = false
            this.selectrow = []
        },
        del() {
            this.$nextTick(() => {
                this.delvisible = true
            })
        },
        refresh() {
            this.getproject()
        },
        handleSizeChange(val) {
            this.pageSize = val
        },
        handleCurrentChange(val) {
            this.currentPage = val
        },
        handlelook(row) {
            console.log(row);
        },
        handleDelete(row) {
            this.selectrow.push(row)
            //console.log(this[`multipleSelection${item.projectid}`]);
            this.del()
        },
        handleSchedule(row) {
            this.$router.push({ path: "/TaskSchedule/", query: { projectid: this.project.id, version: row.verName } })
        },
        handleoutput(row) {
            console.log(row);
        },
        handleiutput(row) {
            console.log(row);
            let a = {}
            a.id = this.project.id
            a.dataType = this.project.dataType
            a.verName = row.verName
            a.versionId=row.versionId
            this.$router.push({ path: "/InputFile", query: a })
        },
        getrowkey(row) {
            return row.verName || row.userId
        },
        handleSelectionChange(val) {
            let a = []
            val.map(item => {
                a.push(item.verName)
            })
            this.multipleSelection = a;
            //console.log(this.multipleSelection);
        },
    },
    mounted() {
        this.project = JSON.parse(this.$route.query.project)
        this.getproject()              //利用projectid获取项目信息
    },
}
</script>
<style scoped>
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

.form {
    font-size: 30px;
}

.formitem {
    width: 80%;
    text-align: left;
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