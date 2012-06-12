<br>
<h1>标题为 : </h1>
<h2>${contentInfo.name}</h2>
<h2> 具体内容为:</h2>

<hr>

<br>
${contentInfo.textData}
<br>
<br>
<a href="delCategaryInfoPrompt?Id=${contentInfo.id}&category=${contentInfo.category}">删除</a>
<a href="editCategaryInfo?Id=${contentInfo.id}" >编辑内容</a>
<a href="displayInfo?category=${contentInfo.category}" >返回</a>

