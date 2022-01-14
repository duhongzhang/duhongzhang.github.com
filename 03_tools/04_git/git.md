# git

## reference

https://git-scm.com/book/zh/v2/

## git commands

### 1. mv：改变文件目录和名字

```shell
#can change name and directory
$git mv sources destnations
```

### 2. log/show：查看文件日志/差分

```shell
$git log [fileName]
$git show [commitId] [fileName]
```

### 3. commit：上传并添加注释

```shell
$git commit -m "comments"
```

### 4. revert：回滚某个提交（server上）

```shell
$git revert [HEAD|commit-id]
```

