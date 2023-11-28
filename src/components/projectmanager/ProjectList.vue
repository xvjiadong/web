<template>
    <div class="container">
        <div class="header">
            <span style="font-size: 16px;color: rgb(21,27,38);">项目列表</span>
            <div style="display: flex;justify-content: space-between;">
                <span style="font-size: 10px;color: rgb(21,27,38);">平台支持统一纳管自训练模型的数据集，并支持自主版本迭代、数据查看、导入导出和删除等操作。</span>
                <span class="hide" @click="hide">
                    {{ hideintroduction ? "展开" : "隐藏" }}使用介绍
                </span>
            </div>
        </div>
        <el-card class="teachcard" v-if="!hideintroduction">
            <div slot="header">
                <span style="font-size: 16px;color: rgb(21,27,38);">
                    产品介绍
                </span>
                <br>
                <div>
                    <span style="font-size: 10px;color: #84868c;">
                        恒生电子数据标注平台为一站式数据处理和服务平台，主要围绕AI模型开发过程中所需的数据采集、数据智能处理、数据标注等环节提供完整的数据服务。目前平台已支持图片、文本两类基础数据的处理，支持信息抽取、文本分类、图像文本、图片分类四大标注任务类型。
                    </span>
                </div>
            </div>
            <div class="teachbody">
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/docget.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            创建项目
                        </div>
                        <div class="itemcontent">
                            支持采集图片类数据，可以从本地接入视频抽帧图片或通过接入云服务调用数据接入图片
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/dockind.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            导入数据
                        </div>
                        <div class="itemcontent">
                            支持采集图片类数据，可以从本地接入视频抽帧图片或通过接入云服务调用数据接入图片
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/picdoc.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            项目调度
                        </div>
                        <div class="itemcontent">
                            支持采集图片类数据，可以从本地接入视频抽帧图片或通过接入云服务调用数据接入图片
                        </div>
                    </div>
                </div>
                <div class="teachbodyitem">
                    <img style="width: 46px;height: 46px;" src="/pickind.svg">
                    <div style="text-align: center;">
                        <div class="itemtitle">
                            数据标注
                        </div>
                        <div class="itemcontent">
                            支持采集图片类数据，可以从本地接入视频抽帧图片或通过接入云服务调用数据接入图片
                        </div>
                    </div>
                </div>
            </div>
        </el-card>
        <el-card class="teachcard">
            <div slot="header" style="display: flex;justify-content: space-between;">
                <el-button type="primary" size="mini" style="background-color: rgb(36,104,242);" @click="create"><i
                        class="el-icon-plus"></i>&emsp;创建项目</el-button>
                <div style="display: flex;">
                    <el-select size="small" v-model="showprojecttype" placeholder="全部">
                        <el-option v-for="item in select" :key="item.label" :value="item.value"></el-option>
                    </el-select>
                    <el-input style="width: 40%;" size="small" v-model="inputvalue" placeholder="请输入项目名称或ID"
                        suffix-icon="el-icon-search">
                    </el-input>
                    <el-button size="mini" @click="refresh"><i class="el-icon-refresh"
                            style="font-size: 15px;"></i></el-button>
                    <el-button size="mini"><i class="el-icon-refresh" style="font-size: 15px;"></i>转让项目</el-button>
                </div>
            </div>
            <div>
                <div v-for="item in showlist.slice((currentPage - 1) * pageSize, pageSize * currentPage)" :key="item.id"
                    class="projectlist">
                    <el-card>
                        <div slot="header" style="display: flex;justify-content: space-between;align-items: center;">
                            <div>
                                <span style="font-size: 12px;color: rgb(21,27,38);">{{ item.name }}</span>&emsp;
                                <span style="font-size: 12px;color: rgb(21,27,38);">项目ID：{{ item.id }}</span>
                            </div>
                            <div>
                                <span class="listheaderitem" @click="add(item)">
                                    <img style="width: 14px;height: 14px;" src="/add.svg">
                                    <span style="font-size: 12px;margin-left: 3px;">新增版本</span>
                                </span>
                                <span class="listheaderitem" @click="detail(item)">
                                    <img style="width: 14px;height: 14px;" src="/all.svg">
                                    <span style="font-size: 12px;margin-left: 3px;">项目详情</span>
                                </span>
                                <span class="listheaderitem" @click="del(item)">
                                    <i style="font-size: 16px;" class="el-icon-delete"></i>
                                    <span style="font-size: 12px;margin-left: 3px;">删除</span>
                                </span>
                            </div>
                        </div>
                        <el-table :ref="`project${item.id}`" :data="item.versions"
                            @selection-change="handleSelectionChange($event, item)" :row-key="getrowkey" :key="fresh">
                            <el-table-column type="selection" width="35" :reserve-selection="true"></el-table-column>
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
                                                    <span @click="a(scope)">{{ item.dataType }}</span>
                                                </template>
                                            </el-table-column>
                                            <el-table-column prop="personalProgress" label="任务进度"></el-table-column>
                                            <el-table-column label="操作">
                                                <template slot-scope="scope">
                                                    <el-button size="mini"
                                                        @click="handleTaskLook(item, scope.row)">查看</el-button>
                                                    <el-button size="mini"
                                                        @click="handletask(item, scope.row)">移交</el-button>
                                                </template>
                                            </el-table-column>
                                        </el-table>
                                    </div>
                                    <div style="text-align:center; " v-else>
                                        <el-empty description="未分配任务" style="padding:0px;color:rgb(21,27,38)">
                                            <span slot @click="handleSchedule(item, scope.row)"
                                                style="color:rgb(36,104,242);cursor: pointer;">
                                                去分配任务
                                            </span>
                                        </el-empty>
                                    </div>
                                </template>
                            </el-table-column>
                            <el-table-column width="150" prop="verName" label="版本"></el-table-column>
                            <el-table-column width="150" prop="dataNumber" label="数据量"></el-table-column>
                            <el-table-column width="150" label="数据类型">
                                <template slot-scope="scope">
                                    <span @click="a(scope)">{{ item.dataType }}</span>
                                </template>
                            </el-table-column>
                            <el-table-column width="120" prop="callType" label="标注类型"></el-table-column>
                            <el-table-column prop="progress" label="标注进度"></el-table-column>
                            <el-table-column label="操作">
                                <template slot-scope="scope">
                                    <span class="tableplay" @click="handleinput(item, scope.row)">导入</span>
                                    <span class="tableplay" @click="handlepredict(item, scope.row)"
                                        v-if="item.dataType === '图像'">预标注</span>
                                    <span v-if="!scope.row.task" class="tableplay"
                                        @click="handleSchedule(item, scope.row)">调度</span>
                                    <span class="tableplay" @click="handleDelete(item, scope.row)">删除</span>
                                    <span class="tableplay" @click="handleOutput(item, scope.row)"
                                        v-if="scope.row.progress === '100%'">导出</span>
                                </template>
                            </el-table-column>
                        </el-table>
                    </el-card>
                </div>
            </div>
        </el-card>
        <el-pagination v-if="projectlist.length !== 0" :current-page="currentPage" :page-sizes="[3, 4, 6, 8]"
            :page-size="pageSize" background layout="sizes, prev, pager, next, jumper" :total="showlist.length"
            @current-change="handleCurrentChange" @size-change="handleSizeChange" />
        <el-dialog title="新增项目版本" :visible.sync="centerDialogVisible" width="40%" :center="false" :destroy-on-close="true"
            :show-close="false" :close-on-click-modal="false">
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
                <el-form-item v-if="isextends" prop="addnewversion.marktype" label="历史版本" class="formitem">
                    <el-select size="mini" v-model="addnewversion.marktype" placeholder="请选择历史版本">
                        <el-option v-for="item in chooseitem.versions" :key="item.id" :value="item.callType"
                            :label="`${item.verName}-${item.callType}`"></el-option>
                    </el-select>
                </el-form-item>
                <el-form-item v-else label="标注类型" prop="addnewversion.marktype" class="formitem">
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
        <el-dialog title="删除数据集" :visible.sync="delvisible" width="24%" top="15%" :destroy-on-close="true"
            :show-close="false" :close-on-click-modal="false">
            <span style="font-size:14px;text-align:left;">{{ deldialogcontent }}</span>
            <span slot="footer" class="dialog-footer">
                <el-button size="mini" type="primary" @click="delok">确 定</el-button>
                <el-button size="mini" @click="delcancel">取 消</el-button>
            </span>
        </el-dialog>
        <el-dialog width="24%" top="15%" title="预测标签添加" :visible.sync="predictvisible" :destroy-on-close="true"
            :show-close="false" :close-on-click-modal="false">
            <div style="display: flex;flex-direction: column;align-items: flex-start;" v-if="chooseitem.callType==='图片分类'">
                <el-input v-model="predictvalue" size="mini" placeholder="请在版本标签基础上新增预定义标签"></el-input>
                <span style="font-size: 12px;color: #84868c;">请以，分隔不同标签</span>
                <span style="font-size: 12px;color: #84868c;">支持为标签添加注释，例如【基金】合同，【第一条】法案</span>
            </div>
            <div v-else>
                 确定进行图像文本预标注吗
            </div>
            <span slot="footer" class="dialog-footer">
                <el-button size="mini" type="primary" @click="predictok">确 定</el-button>
                <el-button size="mini" @click="predictcancel">取 消</el-button>
            </span>
        </el-dialog>
    </div>
</template>
<script>
import axios from 'axios'
//import Project from '../../../public/project.json'
export default {
    name: "ProjectList",
    components: {

    },
    data() {
        return {
            delvisible: false,
            centerDialogVisible: false,
            currentPage: 1,
            pageSize: 3,
            hideintroduction: false,
            select: [{ label: "全部", value: "全部" }, { value: "图像", label: "图像" }, { value: "文本", label: "文本" }],
            showprojecttype: "全部",
            inputvalue: "",
            projectlist: [{
                "id": 25,
                "name": "牛尾花",
                "dataNumber": null,
                "dataType": "图像",
                "versions": [
                    {
                        "verName": "V1",
                        "progress": null,
                        "callType": "点标注",
                        "dataNumber": null,
                        "userVOList": []
                    }
                ]
            },],
            multipleSelection: [],
            addnewversion: {
                versionname: "",
                descript: "",
                marktype: ""
            },
            isextends: true,
            chooseitem: "",
            selectrow: "",
            fresh: false,
            predictvalue: "",
            predictvisible: false
        }
    },
    computed: {
        showlist() {
            return this.projectlist.filter(item => {
                return (item.name.includes(this.inputvalue)) && (this.showprojecttype === "全部" || item.datatype === this.showprojecttype)
            })
        },
        marktypelist() {
            let a = [{ value: "图像分类", label: "图像分类" }, { value: "多边形标注", label: "多边形标注" }, { value: "文本检测", label: "文本检测" }, { value: "点标注", label: "点标注" }, { value: "线标注", label: "线标注" }, { value: "混合标注", label: "混合标注" }]
            let b = [{ value: "关系抽取", label: "关系抽取" }, { value: "证据划选", label: "证据划选" }, { value: "实体抽取", label: "实体抽取" }, { value: "混合标注", label: "混合标注" }]
            if (this.chooseitem.dataType === "图像") {
                return a
            } else if (this.chooseitem.dataType === "文本") {
                return b
            }
            return []
        },
        deldialogcontent() {
            if (!this.delvisible) {
                return ""
            }
            console.log(this[`multipleSelection${this.chooseitem.id}`].length, this.chooseitem.versions.length);
            if (this[`multipleSelection${this.chooseitem.id}`].length === this.chooseitem.versions.length) {
                return "删除后，项目及全部版本数据都将会被删除且不可恢复，确认要删除吗？"
            } else if (this[`multipleSelection${this.chooseitem.id}`].length === 0 && !this.selectrow) {
                return "请选择项目版本进行删除"
            }
            return "删除后，所选项目版本及所归属的任务都将会被删除且不可恢复，确认要删除吗？"
        }
    },
    methods: {
        predictok() {
            /*axios.get("http://192.168.224.150:10010/xxx/" + {id:this.chooseitem.id,verName:this.chooseitem.verName}).then(res => {
                内含版本标签组和标注数据url
                let data = res.data.data.ossPath
                data.label = res.data.data.labels.join(",") + this.predictvalue
                向python后台发送请求标注
                if(this.chooseitem.callType ===图片分类){

                }else{
                    
                }
                获取数据后保存文件发到后台 
            })*/

            setTimeout(() => {
                this.$message.success("预标注完成")
            },2000)
            this.predictcancel()
        },
        predictcancel() {
            this.chooseitem = ""
            this.predictvalue = ""
            this.predictvisible = false
        },
        addcancel() {
            this.centerDialogVisible = false
            this.chooseitem = ""
            this.isextends = true
            this.addnewversion = {
                versionname: "",
                descript: "",
                marktype: ""
            }
        },
        addok() {
            console.log(this.addnewversion);
            if (this.addnewversion.marktype) {
                this.addnewversion.projectid = this.chooseitem.id
                console.log(this.addnewversion);
                let a = {}
                a.id = this.addnewversion.projectid
                a.markType = this.addnewversion.marktype
                a.verAttributes = this.addnewversion.descript
                a.version = this.addnewversion.versionname
                axios.post("http://192.168.224.150:10010/items/version/add", a).then(res => {
                    console.log(res.data);
                })
                this.fresh = !this.fresh
                this.getproject()
                this.$nextTick(() => {
                    this.centerDialogVisible = false
                    this.chooseitem = ""
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
        add(item) {
            this.chooseitem = item
            let a = -1;
            item.versions.forEach(element => {
                let b = parseInt(element.verName.substring(1))
                a = b > a ? b : a
            });
            this.addnewversion.versionname = "V" + (a + 1)
            this.$nextTick(() => {
                this.centerDialogVisible = true
            })
        },
        detail(item) {
            console.log(item);
            let a = JSON.stringify(item)
            this.$router.push({ path: "/ProjectDetail/", query: { project: a } })

        },
        delok() {
            let form
            if (this.selectrow) {
                //console.log(this.selectrow);
                let a = []
                this.selectrow.map(item => {
                    a.push(item.verName)
                })
                //console.log(a);
                form = { id: this.chooseitem.id, versionId: a }
            } else {
                if (this[`multipleSelection${this.chooseitem.id}`].length === this.chooseitem.versions.length) {
                    form = { id: this.chooseitem.id }

                } else if (this[`multipleSelection${this.chooseitem.id}`].length === 0) {
                    this.delcancel()
                    return
                }
                else {
                    form = { id: this.chooseitem.id, versionId: this[`multipleSelection${this.chooseitem.id}`] }
                }
            }
            console.log(form);
            this.delvisible = false
            this.chooseitem = ""
            this.selectrow = ""
            this.$nextTick(() => {
                this.getproject()
                this.projectlist.forEach(item => {
                    this[`multipleSelection${item.id}`] = []
                })
            })
            
            axios.post('http://192.168.224.150:10010/items/delete', form).then((res) => {
                console.log(res.data);
                if (res.data.code === 200) {
                    this.$message({ type: "success", message: "删除完毕" })
                    this.chooseitem = ""
                    this.selectrow = ""
                    this.fresh = !this.fresh
                    this.$nextTick(() => {
                        this.getproject()
                        this.projectlist.forEach(item => {
                            this[`multipleSelection${item.id}`] = []
                        })
                    })
                    this.delvisible = false
                } else {
                    this.$message({ type: "error", message: "删除失败" })
                    this.delvisible = false
                }
            })
        },
        delcancel() {
            this.delvisible = false
            console.log(this.$refs[`project${this.chooseitem.id}`]);
            this[`multipleSelection${this.chooseitem.id}`] = this.$refs[`project${this.chooseitem.id}`][0].selection
            this.selectrow = ""
            this.chooseitem = ""
        },
        del(item) {
            this.chooseitem = item
            this.$nextTick(() => {
                this.delvisible = true
            })
        },
        getproject() {
            axios.get("http://192.168.224.150:10010/items").then((res) => {
                this.projectlist = res.data.data;
                console.log(this.projectlist);
                this.projectlist.forEach(item => {
                    this[`multipleSelection${item.id}`] = []
                })
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
        hide() {
            this.hideintroduction = !this.hideintroduction
        },
        create() {
            this.$router.push("/CreateProject")
        },
        handlepredict(item, row) {
            console.log(item, row);
            this.chooseitem = { id: item.id, verName: row.verName,callType:row.callType }
            this.predictvisible = true

        },
        handleSelectionChange(val, item) {
            let a = []
            val.map(item => {
                a.push(item.verName)
            })
            this[`multipleSelection${item.id}`] = a;
            console.log(this[`multipleSelection${item.id}`]);
            //console.log(this.multipleSelection);
        },
        handleDelete(item, row) {
            let a = []
            a.push(row)
            this.chooseitem = item
            this.selectrow = a
            //console.log(this[`multipleSelection${item.projectid}`]);
            this.del(item)
        },
        handleSchedule(item, row) {
            this.$router.push({ path: "/TaskSchedule/", query: { id: item.id, version: row.versionId } })
        },
        a(item) {
            console.log(item);
        },
        handleOutput(item, row) {
            console.log(item, row);
        },
        handleinput(item, row) {
            console.log(item, row);
            let a = {}
            a.id = item.id
            a.dataType = item.dataType
            a.verName = row.verName
            a.versionId = row.versionId
            this.$router.push({ path: "/InputFile", query: a })
        },
        handleTaskLook(item, row) {
            console.log(item, row);
        },
        handtask(item, row) {
            console.log(item, row);
        },
        getrowkey(row) {
            return row.verName || row.userId
        }
    },
    mounted() {
        this.getproject()

        console.log(axios);
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

.form {
    font-size: 30px;
}

.formitem {
    width: 80%;
    text-align: left;
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