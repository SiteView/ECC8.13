//列表类
//listIdStr 用于承载列表的 HTML 元素的 id 属性名称
//name 列表选择项（checkbox）的 name 属性名称
function CList(listIdStr, name)
{
    this.listIdStr = listIdStr;
    this.listId = document.getElementById(this.listIdStr);
    
    this.name = name;
    
    this.GetLength = GetLength;
    this.InsertItem = InsertItem;
    this.AppendItem = AppendItem;
    this.ModifyItem = ModifyItem;
    this.DeleteItem = DeleteItem;
    this.IsChecked = IsChecked;
    this.SetChecked = SetChecked;
}

//获得列表项数量
function GetLength()
{
    return this.listId.childNodes.length;
}

//index 插入的位置，从 0 开始
//value 列表项的值
//text 列表项的文字
//checked 是否选择当前列表项
function InsertItem(index, value, text, checked)
{
    if (index<0 || index>=this.GetLength())
    {
        return;
    }
    
    var str = "";
    var i = 0;
    for (i=0; i<index; i++)
    {
        str += "<div>" + this.listId.childNodes[index].innerHTML + "</div>";
    }
    
    if (checked)
    {
        str += "<div><input type=\"checkbox\" value=\"" + value + "\" name=\"" + name + "\" checked=\"checked\"><span>" + text + "</span></div>";
    }
    else
    {
        str += "<div><input type=\"checkbox\" value=\"" + value + "\" name=\"" + name + "\"><span>" + text + "</span></div>";
    }
    
    for (i=index; i<this.GetLength(); i++)
    {
        str += "<div>" + this.listId.childNodes[index].innerHTML + "</div>";
    }
    
    this.listId.innerHTML = str;
}

function AppendItem(value, text, checked)
{
    if (checked)
    {
        this.listId.innerHTML += "<div><input type=\"checkbox\" value=\"" + value + "\" name=\"" + name + "\" checked=\"checked\"><span>" + text + "</span></div>";
    }
    else
    {
        this.listId.innerHTML += "<div><input type=\"checkbox\" value=\"" + value + "\" name=\"" + name + "\"><span>" + text + "</span></div>";
    }
}

function ModifyItem(index, value, text, checked)
{
    if (index<0 || index>=this.GetLength())
    {
        return;
    }
    
    if (checked)
    {
        this.listId.childNodes[index].innerHTML = "<input type=\"checkbox\" value=\"" + value + "\" name=\"" + name + "\" checked=\"checked\"><span>" + text + "</span>";
    }
    else
    {
        this.listId.childNodes[index].innerHTML = "<input type=\"checkbox\" value=\"" + value + "\" name=\"" + name + "\"><span>" + text + "</span>";
    }
}

function DeleteItem(index)
{
    if (index<0 || index>=this.GetLength())
    {
        return;
    }
    
    this.listId.removeChild(this.listId.childNodes[index]);
}

function IsChecked(index)
{
    return this.listId.childNodes[index].childNodes[0].getAttribute("checked");
}

function SetChecked(index, checked)
{
    if (index<0 || index>=this.GetLength())
    {
        return;
    }
    
    this.listId.childNodes[index].childNodes[0].setAttribute("checked", checked);
}