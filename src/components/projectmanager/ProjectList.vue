<template>
	<div class="container">
		<div class="header">
			<span style="font-size: 16px; color: rgb(21, 27, 38)">项目列表</span>
			<div style="display: flex; justify-content: space-between">
				<span
					style="font-size: 10px; color: rgb(21, 27, 38)">平台支持统一纳管自训练模型的数据集，并支持自主版本迭代、数据查看、导入导出和删除等操作。</span>
				<span class="hide" @click="hide">
					{{ hideintroduction ? "展开" : "隐藏" }}使用介绍
				</span>
			</div>
		</div>
		<el-card class="teachcard" v-if="!hideintroduction">
			<div slot="header">
				<span style="font-size: 16px; color: rgb(21, 27, 38)"> 产品介绍 </span>
				<br />
				<div>
					<span style="font-size: 10px; color: #84868c">
						数据标注平台为一站式数据处理和服务平台，主要围绕AI模型开发过程中所需的数据采集、数据智能处理、数据标注等环节提供完整的数据服务。目前平台已支持图片、文本两类基础数据的处理，支持信息抽取、文本分类、图像文本、图片分类四大标注任务类型。
					</span>
				</div>
			</div>
			<div class="teachbody">
				<div class="teachbodyitem">
					<img style="width: 46px; height: 46px" src="/docget.svg" />
					<div style="text-align: center">
						<div class="itemtitle">创建项目</div>
						<div class="itemcontent">
							支持采集图片类数据，可以从本地接入视频抽帧图片或通过接入云服务调用数据接入图片
						</div>
					</div>
				</div>
				<div class="teachbodyitem">
					<img style="width: 46px; height: 46px" src="/dockind.svg" />
					<div style="text-align: center">
						<div class="itemtitle">导入数据</div>
						<div class="itemcontent">
							支持采集图片类数据，可以从本地接入视频抽帧图片或通过接入云服务调用数据接入图片
						</div>
					</div>
				</div>
				<div class="teachbodyitem">
					<img style="width: 46px; height: 46px" src="/picdoc.svg" />
					<div style="text-align: center">
						<div class="itemtitle">项目调度</div>
						<div class="itemcontent">
							支持采集图片类数据，可以从本地接入视频抽帧图片或通过接入云服务调用数据接入图片
						</div>
					</div>
				</div>
				<div class="teachbodyitem">
					<img style="width: 46px; height: 46px" src="/pickind.svg" />
					<div style="text-align: center">
						<div class="itemtitle">数据标注</div>
						<div class="itemcontent">
							支持采集图片类数据，可以从本地接入视频抽帧图片或通过接入云服务调用数据接入图片
						</div>
					</div>
				</div>
			</div>
		</el-card>
		<el-card class="teachcard">
			<div slot="header" style="display: flex; justify-content: space-between">
				<el-button type="primary" size="mini" style="background-color: rgb(36, 104, 242)" @click="create"><i
						class="el-icon-plus"></i>&emsp;创建项目</el-button>
				<div style="display: flex">
					<el-select size="small" v-model="showprojecttype" placeholder="全部">
						<el-option v-for="item in select" :key="item.label" :value="item.value"></el-option>
					</el-select>
					<el-input style="width: 40%" size="small" v-model="inputvalue" placeholder="请输入项目名称或ID"
						suffix-icon="el-icon-search">
					</el-input>
					<el-button size="mini" @click="refresh"><i class="el-icon-refresh"
							style="font-size: 15px"></i></el-button>
					<el-button size="mini"><i class="el-icon-refresh" style="font-size: 15px"></i>转让项目</el-button>
				</div>
			</div>
			<div v-loading="loading">
				<div v-for="item in projectlist" :key="item.id" class="projectlist">
					<el-card>
						<div slot="header" style="
                display: flex;
                justify-content: space-between;
                align-items: center;
              ">
							<div>
								<span style="font-size: 12px; color: rgb(21, 27, 38)">{{
					item.name
				}}</span>&emsp;
								<span style="font-size: 12px; color: rgb(21, 27, 38)">项目ID：{{ item.id }}</span>
							</div>
							<div>
								<span class="listheaderitem" @click="add(item)">
									<img style="width: 14px; height: 14px" src="/add.svg" />
									<span style="font-size: 12px; margin-left: 3px">新增版本</span>
								</span>
								<span class="listheaderitem" @click="detail(item)">
									<img style="width: 14px; height: 14px" src="/all.svg" />
									<span style="font-size: 12px; margin-left: 3px">项目详情</span>
								</span>
								<span class="listheaderitem" @click="del(item)">
									<i style="font-size: 16px" class="el-icon-delete"></i>
									<span style="font-size: 12px; margin-left: 3px">删除</span>
								</span>
							</div>
						</div>
						<el-table :ref="`project${item.id}`" :data="item.versions"
							@selection-change="handleSelectionChange($event, item)" :row-key="getrowkey" :key="fresh">
							<el-table-column type="selection" width="35" :reserve-selection="true"></el-table-column>
							<el-table-column type="expand" width="55" label="任务">
								<template slot-scope="scope">
									<div style="text-align: center" v-if="scope.row.userVOList">
										<el-table :data="scope.row.userVOList">
											<el-table-column prop="dataNumber" label="任务数量"></el-table-column>
											<el-table-column prop="username" label="任务承办人"></el-table-column>
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
									<div style="text-align: center" v-else>
										<el-empty description="未分配任务" style="padding: 0px; color: rgb(21, 27, 38)">
											<span slot @click="handleSchedule(item, scope.row)"
												style="color: rgb(36, 104, 242); cursor: pointer">
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
										v-if="scope.row.pre === 'false'">智能标注</span>
									<!-- <el-tooltip content="至少标注20份，已使用的标签至少使用过10次才能启用" placement="top-start">
                                        <span class="tableplay" @click="mid_predict(item, scope.row)">自动标注</span>
                                    </el-tooltip> -->
									<el-tooltip v-if="scope.row.pre === 'error'" content="产生错误，已停止自动标注，请重新设置自动标注任务"
										placement="top-start">
										<span class="tableplay" @click="handlepredict(item, scope.row)">智能标注</span>
									</el-tooltip>
									<span v-if="item.dataType === '图像'" @click="generate_appear(scope.row)"
										class="tableplay">增强</span>
									<span v-if="scope.row.callType === '分割标注'" @click="picedit(item, scope.row)"
										class="tableplay">编辑</span>
									<span class="tableplay" v-if="scope.row.pre.includes('ing')">标注中</span>
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
		<el-pagination v-if="projectlist.length !== 0" :hide-on-single-page="true" :current-page="currentPage"
			:page-sizes="[5]" :page-size="5" background layout="sizes, prev, pager, next, jumper" :total="total"
			@current-change="handleCurrentChange" />
		<el-dialog title="新增项目版本" :visible.sync="centerDialogVisible" width="40%" :center="false"
			:destroy-on-close="true" :show-close="false" :close-on-click-modal="false">
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
			<span style="font-size: 14px; text-align: left">{{
					deldialogcontent
				}}</span>
			<span slot="footer" class="dialog-footer">
				<el-button size="mini" type="primary" @click="delok">确 定</el-button>
				<el-button size="mini" @click="delcancel">取 消</el-button>
			</span>
		</el-dialog>
		<el-dialog width="24%" top="15%" title="预测标签添加" :visible.sync="predictvisible" :destroy-on-close="true"
			:show-close="false" :close-on-click-modal="false">
			<div style="display: flex; flex-direction: column; align-items: flex-start"
				v-if="chooseitem.callType === '图片分类'">
				<el-input v-model="predictvalue" size="mini" placeholder="请在版本标签基础上新增预定义标签"></el-input>
				<span style="font-size: 12px; color: #84868c">请以，分隔不同标签</span>
				<span style="font-size: 12px; color: #84868c">支持为标签添加注释，例如【基金】合同，【第一条】法案</span>
			</div>
			<div v-else>确定进行图像文本预标注吗</div>
			<span slot="footer" class="dialog-footer">
				<el-button size="mini" type="primary" @click="predictok">确 定</el-button>
				<el-button size="mini" @click="predictcancel">取 消</el-button>
			</span>
		</el-dialog>
		<el-dialog title="请选择处理对象" :visible.sync="segvis" width="24%" top="15%" :destroy-on-close="true"
			:show-close="false" :close-on-click-modal="false">
			<div v-if="chooseitem.callType == '分割标注' || chooseitem.callType == '物体检测'
					" style="
          display: flex;
          justify-content: space-around;
          width: 100%;
          height: 100%;
        ">
				<el-checkbox-group v-model="segclass" style="width: 40%; height: 250px; overflow-y: scroll">
					<el-checkbox v-for="(item, index) in labeldata" :label="index" :key="index" style="float: left">
						<span style="font: 0.8em sans-serif">{{ item.name }}</span>
					</el-checkbox>
				</el-checkbox-group>
				<div style="
            width: 40%;
            height: 250px;
            overflow-y: scroll;
            display: flex;
            flex-direction: column;
            align-items: flex-start;
          ">
					<el-input v-model="predicttext" type="textarea"
						placeholder="如果没有希望分割的选项，请再此输入分割或检测对象，不同对象之间以空格隔开"></el-input>
				</div>
			</div>
			<span slot="footer" class="dialog-footer">
				<el-tooltip v-if="segclass.length == 0 &&
					(chooseitem.callType == '分割标注' ||
						chooseitem.callType == '物体检测')
					" content="未选择类别，将自动处理所有对象" placement="top-start"><el-button size="mini" type="primary" @click="predictok">确
						定</el-button></el-tooltip>
				<el-button v-else size="mini" type="primary" @click="predictok">确 定</el-button>
				<el-button size="mini" @click="predictcancel">取 消</el-button>
			</span>
		</el-dialog>
		<el-dialog title="确定要进行文本智能标注吗？" :visible.sync="textvis" width="24%" top="15%" :destroy-on-close="true"
			:show-close="false" :close-on-click-modal="false">
			<el-card v-if="!(
					chooseitem.callType === '关键词抽取' ||
					chooseitem.callType === '生成式摘要' ||
					chooseitem.callType === '抽取式阅读理解'
				)
					" style="width: 100%">
				<div slot="header">
					<div v-if="!addlabelvisible && !addlabelgroupvisible"
						style="display: flex; justify-content: space-between">
						<div>
							<el-button style="
                  background-color: rgb(36, 104, 242);
                  font-size: 12px;
                  color: white;
                " size="mini" @click="addlabelvisible = true">
								<i class="el-icon-price-tag"></i>
								添加标签
							</el-button>
							<el-button style="
                  background-color: rgb(36, 104, 242);
                  font-size: 12px;
                  color: white;
                " size="mini" @click="addlabelgroupvisible = true">
								<i class="el-icon-guide"></i>
								添加标签组
							</el-button>
						</div>
					</div>
					<div v-if="addlabelvisible" style="
              display: flex;
              flex-direction: column;
              align-items: left;
              justify-content: flex-start;
            ">
						<div style="display: flex; justify-content: left; align-items: center">
							<input class="input" size="mini" v-model="labelvalue" placeholder="请输入标签名称，不支持重复标签" />
							<i class="el-icon-check labelicon" @click="surelabelinput"></i>
							<i class="el-icon-close labelicon" @click="closelabelinput"></i>
						</div>
						<span v-if="emptylabel" id="repeattext" class="animate__animated animate__shakeX">
							{{ labelerror }}
						</span>
						<span v-else class="suretext" :class="{ addok: labelsure !== '待添加' }">
							{{ labelsure }}
						</span>
					</div>
					<div v-if="addlabelgroupvisible" style="
              display: flex;
              flex-direction: column;
              align-items: left;
              justify-content: flex-start;
            ">
						<div style="display: flex; justify-content: left; align-items: center">
							<select v-model="selectlabelgroup" class="input">
								<option v-for="item in labelgroup" :key="item.id" :value="item.id" :label="item.name">
								</option>
							</select>
							<i class="el-icon-check labelicon" @click="surelabelgroupselect"></i>
							<i class="el-icon-close labelicon" @click="closelabelgroupselect"></i>
						</div>
						<span v-if="emptylabel" id="repeattext" class="animate__animated animate__shakeX">
							{{ labelerror }}
						</span>
						<span v-else class="suretext" :class="{ addok: labelsure !== '待添加' }">
							{{ labelsure }}
						</span>
					</div>
				</div>
				<div style="display: flex; justify-content: left">
					<span>序号</span>
					<span style="margin-left: 15px">标签名</span>
				</div>
				<div style="height: 160px; overflow-y: scroll">
					<div v-for="(item, index) in chooselabel" :key="index" style="display: flex; justify-content: left">
						<div>
							{{ index + 1 }}
						</div>
						<div v-if="!setlabel.includes(index + 1)" style="
                margin-left: 25px;
                display: flex;
                justify-content: left;
                align-items: center;
              ">
							<div class="labelblock" :id="`labeldiv${index + 1}`">
								{{ item }}
							</div>
							<el-tooltip content="编辑标签" placement="top-start">
								<i class="el-icon-edit labelicon" @click="editlabel(index + 1)"></i>
							</el-tooltip>
							<el-tooltip content="删除标签" placement="top-end">
								<i class="el-icon-delete labelicon" @click="deletelabel(index + 1)"></i>
							</el-tooltip>
						</div>
						<div v-else style="
                margin-left: 25px;
                display: flex;
                justify-content: left;
                align-items: center;
              ">
							<input :value="task.selectlabel[index]" class="inputlabel" :id="`labelinput${index + 1}`" />
							<el-tooltip content="保存编辑" placement="top-start">
								<i class="el-icon-check labelicon" @click="editsure(index + 1)"></i>
							</el-tooltip>
							<el-tooltip content="取消编辑" placement="top-end">
								<i class="el-icon-close labelicon" @click="canceledit(index + 1)"></i>
							</el-tooltip>
						</div>
					</div>
				</div>
			</el-card>
			<span slot="footer" class="dialog-footer">
				<el-button :disabled="chooselabel.length == 0 &&
					!(
						chooseitem.callType === '关键词抽取' ||
						chooseitem.callType === '生成式摘要' ||
						chooseitem.callType === '抽取式阅读理解'
					)
					" size="mini" type="primary" @click="predictok">确 定</el-button>
				<el-button size="mini" @click="predictcancel">取 消</el-button>
			</span>
		</el-dialog>
		<el-dialog title="批量处理" :visible.sync="delete_entity_vis" width="24%" top="15%">
			<el-radio-group v-model="replace_or_delete" size="small">
				<el-radio-button label="删除"></el-radio-button>
				<el-radio-button label="替换"></el-radio-button>
			</el-radio-group>
			<div v-if="replace_or_delete === '删除'">
				<el-input v-model="delete_attribute.delete_entity" size="mini" placeholder="请输入删除主体"></el-input>
				<el-select v-model="delete_attribute.delete_entity" size="mini" placeholder="请从已标注的标签中选择">
					<el-option v-for="item in delete_entity_label" :key="item.id + '-' + item.label"
						:value="item.label">
					</el-option>
				</el-select>
				<div slot="footer">
					<div style="width: 100%; display: flex; justify-content: space-around">
						<el-button type="primary" @click="delete_entity_ok">确定</el-button>
						<el-button @click="delete_entity_cancel">取消</el-button>
					</div>
					<span @click="gotoedit" style="
            font-size: 12px;
            color: rgb(64, 184, 255);
            text-decoration: underline;
            cursor: pointer;
          ">详细编辑请点击此处跳转</span>
				</div>
			</div>
			<div v-else>
				<el-input v-model="replaceform.original" size="mini" placeholder="请输入替换主体"></el-input>
				<el-input v-model="replaceform.prompt" placeholder="请输入提示词" size="small" style="width: 80%"></el-input>
				<el-input-number size='small' v-model="replaceform.generate" :min="1" label="请输入生成数量"></el-input-number>
				<div slot="footer">
					<div style="width: 100%; display: flex; justify-content: space-around">
						<el-button type="primary" @click="replace_ok">确定</el-button>
						<el-button @click="delete_entity_ok">取消</el-button>
					</div>
				</div>
			</div>
		</el-dialog>
		<el-dialog title="请填写增强配置" :visible.sync="generatevis" width="24%" top="15%">
			<el-input v-model="generate.prompt" placeholder="请输入提示词" size="small" style="width: 80%"></el-input>
			<el-input-number v-model="generate.number" :min="1" label="请输入生成数量"></el-input-number>
			<div slot="footer">
				<div style="width: 100%; display: flex; justify-content: space-around">
					<el-button type="primary" @click="generate_ok">确定</el-button>
					<el-button @click="generate_cancel">取消</el-button>
				</div>
			</div>
		</el-dialog>
	</div>
</template>

<script>
import axios from "axios";
import labeldata from "../../assets/final_label.json";
//import Project from '../../../public/project.json'
export default {
	name: "ProjectList",
	components: {},
	data() {
		return {
			loading: false,
			total: 0,
			delvisible: false,
			centerDialogVisible: false,
			currentPage: 1,
			pageSize: 5,
			hideintroduction: false,
			select: [
				{ label: "全部", value: "全部" },
				{ value: "图像", label: "图像" },
				{ value: "文本", label: "文本" },
			],
			showprojecttype: "全部",
			inputvalue: "",
			projectlist: [],
			multipleSelection: [],
			addnewversion: {
				versionname: "",
				descript: "",
				marktype: "",
			},
			isextends: true,
			chooseitem: "",
			selectrow: "",
			fresh: false,
			predictvalue: "",
			predictvisible: false,
			segclass: [],
			segvis: false,
			labeldata: [],
			predicttext: "",
			textvis: false,
			chooselabel: [],
			addlabelvisible: false,
			addlabelgroupvisible: false,
			emptylabel: false,
			labelerror: "",
			labelsure: "待添加",
			labelgroup: [],
			selectlabelgroup: "",
			inputvalue2: "",
			setlabel: [],
			delete_entity_label: [],
			delete_entity_vis: false,
			delete_attribute: {
				delete_version: "",
				delete_entity: "",
			},
			generatevis: false,
			generate: {
				id: 0,
				number: 1,
				prompt: "",
			},
			replace_or_delete: "删除",
			replaceform: {
				versionId: 0,
				generate: 1,
				original: "",
				prompt: "",
			},
			editform: {
				projectid: 0,
				projectName: "",
				version: '',
				versionId: 0,
				callType: ""
			}
		};
	},
	computed: {
		marktypelist() {
			let a = [
				{ value: "分割标注", label: "分割标注" },
				{ value: "物体检测", label: "物体检测" },
				{ value: "图像文本标注", label: "图像文本标注" },
				{ value: "图片分类标注/单标签", label: "图片分类标注/单标签" },
				{ value: "图片分类标注/多标签", label: "图片分类标注/多标签" },
				{ value: "多边形标注", label: "多边形标注" },
				{ value: "点标注", label: "点标注" },
				{ value: "线标注", label: "线标注" },
				{ value: "混合标注", label: "混合标注" },
			];
			let b = [
				{ value: "关系抽取", label: "关系抽取" },
				{ value: "证据划选", label: "证据划选" },
				{ value: "实体抽取", label: "实体抽取" },
				{ value: "混合标注", label: "混合标注" },
			];
			if (this.chooseitem.dataType === "图像") {
				return a;
			} else if (this.chooseitem.dataType === "文本") {
				return b;
			}
			return [];
		},
		deldialogcontent() {
			if (!this.delvisible) {
				return "";
			}
			console.log(
				this[`multipleSelection${this.chooseitem.id}`].length,
				this.chooseitem.versions.length
			);
			if (
				this[`multipleSelection${this.chooseitem.id}`].length ===
				this.chooseitem.versions.length
			) {
				return "删除后，项目及全部版本数据都将会被删除且不可恢复，确认要删除吗？";
			} else if (
				this[`multipleSelection${this.chooseitem.id}`].length === 0 &&
				!this.selectrow
			) {
				return "请选择项目版本进行删除";
			}
			return "删除后，所选项目版本及所归属的任务都将会被删除且不可恢复，确认要删除吗？";
		},
	},
	methods: {
		replace_ok() {
			axios.post("http://10.99.212.243:8000/update/all", this.replaceform)
				.then(res => {
					console.log(res);
				})
				.catch(e => {
					console.log(e);
				})
			this.delete_entity_cancel();
		},
		generate_ok() {
			if (this.generate.prompt == "") {
				this.$message.error("请填写提示词");
				return;
			}
			axios
				.post("http://10.99.212.243:8000/sdxl", this.generate)
				.then((res) => {
					if (res.data.code === 200) {
						this.$message.success("生成完毕，请前往图片生成图筛选图片");
					}
				})
				.catch((e) => {
					console.log(e);
					this.$message.error("删除失败");
				});
			this.generate_cancel();
		},
		generate_cancel() {
			this.generatevis = false;
			this.generate = {
				id: 0,
				number: 1,
				prompt: "",
			};
		},
		generate_appear(row) {
			this.generatevis = true;
			this.generate.id = row.versionId;
		},
		gotoedit() {
			this.$router.push({
				path: "/EditPic",
				query: this.editform,
			});
		},
		delete_entity_ok() {
			console.log(this.delete_attribute);
			axios
				.post("http://10.99.212.243:8000/remove/all", {
					versionId: this.delete_attribute.delete_version,
					name: this.delete_attribute.delete_entity,
				})
				.then((res) => {
					if (res.data.code === 200) {
						this.$message.success("删除完毕");
					}
				})
				.catch((e) => {
					console.log(e);
					this.$message.error("删除失败");
				});
			this.delete_entity_cancel();
		},
		delete_entity_cancel() {
			this.detete_entity_vis = false;
			this.delete_entity_label = [];
			this.delete_attribute = {
				detele_version: "",
				delete_entity: "",
			};
			this.editform = {
				projectid: 0,
				projectName: "",
				version: '',
				versionId: 0,
				callType: ""
			}
			this.replaceform = {
				versionId: 0,
				generate: 1,
				original: "",
				prompt: "",
			}
		},
		picedit(item, row) {
			this.editform.projectid = item.id
			this.editform.projectName = item.name
			this.editform.version = row.verName
			this.editform.versionId = row.versionId
			this.editform.callType = row.callType
			axios
				.get("http://120.26.142.114:10010/task/label/" + row.versionId)
				.then((res) => {
					this.delete_entity_label = res.data.data;
					this.delete_entity_vis = true;
					this.delete_attribute.delete_version = row.versionId;
					this.replaceform.versionId = row.versionId
				})
				.catch((e) => {
					console.log(e);
				});
		},
		editlabel(id) {
			this.setlabel.push(id);
			this.$nextTick(() => {
				document.getElementById("labelinput" + id).focus();
			});
		},
		editsure(id) {
			if (document.getElementById("labelinput" + id).value === "") {
				document.getElementById("labelinput" + id).value = "标签名称不能为空";
				document.getElementById("labelinput" + id).classList.add("repeatlabel");
				setTimeout(() => {
					document
						.getElementById("labelinput" + id)
						.classList.remove("repeatlabel");
					document.getElementById("labelinput" + id).value =
						this.chooselabel[id - 1];
				}, 800);
			} else if (
				!this.chooselabel.includes(
					document.getElementById("labelinput" + id).value
				) ||
				this.chooselabel[id - 1] ===
				document.getElementById("labelinput" + id).value
			) {
				this.chooselabel[id - 1] = document.getElementById(
					"labelinput" + id
				).value;
				this.setlabel = this.setlabel.filter((item) => {
					return item !== id;
				});
			} else {
				document.getElementById("labelinput" + id).value = "标签名称重复";
				document.getElementById("labelinput" + id).classList.add("repeatlabel");
				setTimeout(() => {
					document
						.getElementById("labelinput" + id)
						.classList.remove("repeatlabel");
					document.getElementById("labelinput" + id).value =
						this.chooselabel[id - 1];
				}, 800);
			}
		},
		deletelabel(id) {
			this.chooselabel.splice(id - 1, 1);
		},
		canceledit(id) {
			this.setlabel = this.setlabel.filter((item) => {
				return item !== id;
			});
		},
		surelabelinput() {
			if (this.labelvalue && !this.chooselabel.includes(this.labelvalue)) {
				this.chooselabel.push(this.labelvalue);
				this.labelvalue = "";
				this.labelsure = "添加成功";
				this.emptylabel = false;
				return;
			} else if (this.labelvalue === "") {
				this.labelerror = "标签名称不能为空";
				this.emptylabel = true;
			} else {
				this.labelerror = "标签名称重复";
				this.emptylabel = true;
			}
		},
		closelabelinput() {
			this.labelvalue = "";
			this.emptylabel = false;
			this.addlabelvisible = false;
		},
		surelabelgroupselect() {
			if (this.selectlabelgroup === "") {
				this.labelerror = "请选择标签组";
				this.emptylabel = true;
			} else {
				axios
					.get(
						"http://120.26.142.114:10010/label/group/" + this.selectlabelgroup
					)
					.then((res) => {
						let data = res.data.data;
						let a = [];
						data.map((item) => {
							if (this.chooselabel.includes(item.labels)) {
								a.push(item.labels);
							} else {
								this.chooselabel.push(item.labels);
							}
						});
						if (a.length > 0) {
							this.labelerror = "以下标签名称重复：";
							a.forEach((item) => {
								this.labelerror += item + "  ";
							});
							this.emptylabel = true;
						} else {
							this.labelsure = "添加成功";
							this.emptylabel = false;
						}
					});
			}
		},
		closelabelgroupselect() {
			this.selectlabelgroup = "";
			this.addlabelgroupvisible = false;
			this.emptylabel = false;
		},
		mid_predict(item, row) {
			if (row.callType === "物体检测") {
				axios
					.post("http://localhost:5000/api/train_detect", { id: row.versionId })
					.then((res) => {
						console.log(res.data);
						if (res.data === "ok") {
							this.getproject();
						}
					})
					.catch((e) => {
						console.log(e);
						this.$message.error("标注失败");
					});
			} else if (item.callType === "分割标注") {
				axios
					.post("http://localhost:5000/api/segment_predict", {
						id: item.id,
						class: this.segclass,
						text: this.predicttext,
					})
					.then((res) => {
						if (res.data === "ok") {
							this.getproject();
						}
					})
					.catch((e) => {
						console.log(e);
					});
			} else if (
				item.callType === "图片分类标注/单标签" ||
				item.callType === "图片分类标注/多标签"
			) {
				axios
					.post("http://localhost:5000/api/image_classification", {
						id: item.id,
						class: this.segclass,
					})
					.then((res) => {
						if (res.data === "ok") {
							this.getproject();
						}
					})
					.catch((e) => {
						console.log(e);
					});
			} else if (item.callType === "图像文本标注") {
				axios
					.post("http://localhost:5000/api/image_ocr", { id: item.id })
					.then((res) => {
						if (res.data === "ok") {
							this.getproject();
						} else {
							this.$message.error("标注出现问题，请重新开始智能标注");
						}
					})
					.catch((e) => {
						console.log(e);
					});
			}
			this.predictcancel();
		},
		handlepredict(item, row) {
			console.log(item);
			console.log(row);
			this.chooseitem = {
				id: row.versionId,
				verName: row.verName,
				callType: row.callType,
			};
			if (
				row.callType === "分割标注" ||
				row.callType === "物体检测" ||
				row.callType.includes("图片分类标注") ||
				row.callType === "图像文本标注"
			) {
				this.segvis = true;
			} else {
				this.textvis = true;
			}
		},
		predictok() {
			let item = this.chooseitem;
			console.log(item);
			if (item.callType === "物体检测") {
				axios
					.post("http://localhost:5000/api/detect_predict", {
						id: item.id,
						class: this.segclass,
						text: this.predicttext,
					})
					.then((res) => {
						console.log(res.data);
						if (res.data === "ok") {
							this.getproject();
						}
					})
					.catch((e) => {
						console.log(e);
					});
			} else if (item.callType === "分割标注") {
				axios
					.post("http://localhost:5000/api/segment_predict", {
						id: item.id,
						class: this.segclass,
						text: this.predicttext,
					})
					.then((res) => {
						if (res.data === "ok") {
							this.getproject();
						}
					})
					.catch((e) => {
						console.log(e);
					});
			} else if (item.callType.includes("图片分类标注")) {
				axios
					.post("http://localhost:5000/api/image_classification", {
						id: item.id,
						class: this.segclass,
					})
					.then((res) => {
						if (res.data === "ok") {
							this.getproject();
						}
					})
					.catch((e) => {
						console.log(e);
					});
			} else if (item.callType === "图像文本标注") {
				axios
					.post("http://localhost:8800/api/image_ocr", { id: item.id })
					.then((res) => {
						if (res.data === "ok") {
							this.getproject();
						} else {
							this.$message.error("标注出现问题，请重新开始智能标注");
						}
					})
					.catch((e) => {
						console.log(e);
					});
			} else if (
				item.callType === "文本分类" ||
				item.callType === "新闻分类" ||
				item.callType === "情感分析" ||
				item.callType === "意图识别" ||
				item.callType === "自然语言推理"
			) {
				axios
					.post("http://120.26.142.114:10010/task/label", {
						labels: this.chooselabel,
						versionId: item.id,
					})
					.then((res) => {
						if (res.data.code === 200) {
							axios
								.post("http://localhost:5000/api/text_process", {
									id: item.id,
									task: item.callType,
								})
								.then((res) => {
									if (res.data == "ok") {
										this.getproject();
									}
								})
								.catch((e) => {
									console.log(e);
								});
						}
					})
					.catch((e) => {
						console.log(e);
					});
			} else if (
				item.callType === "生成式摘要" ||
				item.callType === "关键词抽取" ||
				item.callType === "抽取式阅读理解"
			) {
				axios
					.post("http://localhost:5000/api/text_process", {
						id: item.id,
						task: item.callType,
					})
					.then((res) => {
						if (res.data == "ok") {
							this.getproject();
						}
					})
					.catch((e) => {
						console.log(e);
					});
			}
			this.predictcancel();
		},
		predictcancel() {
			this.chooseitem = "";
			this.predictvalue = "";
			this.predictvisible = false;
			this.segvis = false;
			this.segclass = [];
			this.predicttext = "";
			this.textvis = false;
			this.chooselabel = [];
			this.addlabelvisible = false;
			this.addlabelgroupvisible = false;
			this.emptylabel = false;
			this.labelerror = "";
			this.labelsure = "待添加";
			this.labelgroup = [];
			this.selectlabelgroup = "";
			this.inputvalue2 = "";
			this.setlabel = [];
		},
		addcancel() {
			this.centerDialogVisible = false;
			this.chooseitem = "";
			this.isextends = true;
			this.addnewversion = {
				versionname: "",
				descript: "",
				marktype: "",
			};
		},
		addok() {
			console.log(this.addnewversion);
			if (this.addnewversion.marktype) {
				this.addnewversion.projectid = this.chooseitem.id;
				console.log(this.addnewversion);
				let a = {};
				a.id = this.addnewversion.projectid;
				a.markType = this.addnewversion.marktype;
				a.verAttributes = this.addnewversion.descript;
				a.version = this.addnewversion.versionname;
				axios
					.post("http://120.26.142.114:10010/items/version/add", a)
					.then((res) => {
						console.log(res.data);
					});
				this.fresh = !this.fresh;
				this.getproject();
				this.$nextTick(() => {
					this.centerDialogVisible = false;
					this.chooseitem = "";
					this.isextends = true;
					this.addnewversion = {
						versionname: "",
						descript: "",
						marktype: "",
					};
				});
			} else {
				this.$message({ type: "error", message: "请选择标注类型" });
			}
		},
		add(item) {
			this.chooseitem = item;
			let a = -1;
			item.versions.forEach((element) => {
				let b = parseInt(element.verName.substring(1));
				a = b > a ? b : a;
			});
			this.addnewversion.versionname = "V" + (a + 1);
			this.$nextTick(() => {
				this.centerDialogVisible = true;
			});
		},
		detail(item) {
			console.log(item);
			let a = JSON.stringify(item);
			this.$router.push({ path: "/ProjectDetail/", query: { project: a } });
		},
		delok() {
			let form;
			if (this.selectrow) {
				//console.log(this.selectrow);
				let a = [];
				this.selectrow.map((item) => {
					a.push(item.verName);
				});
				//console.log(a);
				form = { id: this.chooseitem.id, versionId: a };
			} else {
				if (
					this[`multipleSelection${this.chooseitem.id}`].length ===
					this.chooseitem.versions.length
				) {
					form = { id: this.chooseitem.id };
				} else if (
					this[`multipleSelection${this.chooseitem.id}`].length === 0
				) {
					this.delcancel();
					return;
				} else {
					form = {
						id: this.chooseitem.id,
						versionId: this[`multipleSelection${this.chooseitem.id}`],
					};
				}
			}
			console.log(form);
			this.delvisible = false;
			this.chooseitem = "";
			this.selectrow = "";
			axios
				.post("http://120.26.142.114:10010/items/delete", form)
				.then((res) => {
					console.log(res.data);
					if (res.data.code === 200) {
						this.$message({ type: "success", message: "删除完毕" });
						this.chooseitem = "";
						this.selectrow = "";
						this.fresh = !this.fresh;
						this.getproject();
						this.projectlist.forEach((item) => {
							this[`multipleSelection${item.id}`] = [];
						});
						this.delvisible = false;
					} else {
						this.$message({ type: "error", message: "删除失败" });
						this.delvisible = false;
					}
				});
		},
		delcancel() {
			this.delvisible = false;
			console.log(this.$refs[`project${this.chooseitem.id}`]);
			this[`multipleSelection${this.chooseitem.id}`] =
				this.$refs[`project${this.chooseitem.id}`][0].selection;
			this.selectrow = "";
			this.chooseitem = "";
		},
		del(item) {
			this.chooseitem = item;
			this.$nextTick(() => {
				this.delvisible = true;
			});
		},
		getproject(page) {
			this.loading = true;
			axios
				.get(
					"http://120.26.142.114:10010/items?current=" + page + "&pageSize=" + 5
				)
				.then((res) => {
					if (res.data.code === 200) {
						console.log(1);
						if (res.data.data.length > 0) {
							this.$message.warning("已经是最后一页了");
							return;
						}
						this.total = res.data.data.total;
						this.projectlist = res.data.data.list;
						this.projectlist.forEach((item) => {
							this[`multipleSelection${item.id}`] = [];
						});
						this.currentPage = page;
						this.loading = false;
					}
				})
				.catch((e) => {
					console.log(e);
				});
		},
		refresh() {
			this.getproject();
		},
		handleCurrentChange(val) {
			console.log(val);
			this.getproject(val);
		},
		hide() {
			this.hideintroduction = !this.hideintroduction;
		},
		create() {
			this.$router.push("/CreateProject");
		},
		handleSelectionChange(val, item) {
			let a = [];
			val.map((item) => {
				a.push(item.verName);
			});
			this[`multipleSelection${item.id}`] = a;
			console.log(this[`multipleSelection${item.id}`]);
			//console.log(this.multipleSelection);
		},
		handleDelete(item, row) {
			let a = [];
			a.push(row);
			this.chooseitem = item;
			this.selectrow = a;
			//console.log(this[`multipleSelection${item.projectid}`]);
			this.del(item);
		},
		handleSchedule(item, row) {
			this.$router.push({
				path: "/TaskSchedule/",
				query: { id: item.id, version: row.versionId, callType: row.callType },
			});
		},
		a(item) {
			console.log(item);
		},
		handleOutput(item, row) {
			console.log(item, row);
		},
		handleinput(item, row) {
			console.log(item, row);
			let a = {};
			a.id = item.id;
			a.dataType = item.dataType;
			a.verName = row.verName;
			a.versionId = row.versionId;
			a.page = Math.ceil(this.currentPage / 2);
			this.$router.push({ path: "/InputFile", query: a });
		},
		handleTaskLook(item, row) {
			console.log(item, row);
		},
		handtask(item, row) {
			console.log(item, row);
		},
		getrowkey(row) {
			return row.verName || row.userId;
		},
		getlabelgroup() {
			axios.get("http://120.26.142.114:10010/label").then((res) => {
				//console.log(res.data);
				this.labelgroup = res.data.data;
			});
		},
	},
	mounted() {
		this.getproject(this.currentPage);
		this.getlabelgroup();
		this.labeldata = labeldata;
	},
};
</script>

<style scoped>
@import url("../../../node_modules/animate.css/animate.min.css");

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
	margin-top: 15px;
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
