## Git提交步骤

\1. 拉取远程仓库中的文件                                **git pull**
\2. cd进入项目，查看远程分支                            **git branch** 
\3. 切换分支                                           **git checkout "本地创建分支名"  origin/"远程分支名"**
\4. 提交所以改动文件到Git管理                           **git add .**   
\5. 将已被Git管理的文件提交到本地仓库                    ***\*git conmmit -m "描述"\****
\6. 为了防止发生冲突在push前先git pull 重新拉取下远程的文件
\7. 提交文件到远程                                     **git push**   

## Git使用 

### Git基本使用

`git status`: 查看仓库

`git add filename`：将文件添加到暂存区

`git commit -m yourcomment`: 将文件提交到版本库

`git log`： 提交日志

### Git文件撤销

`git commit --amend`:撤销上一次提交，并将暂存区的文件重新提交

`git checkout -- filename`: 撤销工作区修改，拉取暂存区的文件并将其替换工作区文件

`git reset HEAD filename`: 撤销暂存区修改 ，拉取最近一次提交的版本库中的对应文件到暂存区（HEAD是log中的commit记录的最新记录的id）





























