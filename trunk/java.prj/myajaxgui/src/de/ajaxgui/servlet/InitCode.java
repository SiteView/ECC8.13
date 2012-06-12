package de.ajaxgui.servlet;

import de.ajaxgui.ext.ComponentManager;
import de.ajaxgui.ext.JsGenerator;
import de.ajaxgui.ext.Loading;

public class InitCode {
	private Loading loading = null;

	private String servlet = ComponentManager.get().getServletURI();

	public InitCode() {
		JsGenerator jg = JsGenerator.get();
		jg.addLine("<html><head>");
		jg.addLine("<meta http-equiv=\"expires\" content=\"0\">");
		jg.addLine("<meta http-equiv=\"pragma\" content=\"no-cache\">");
		jg.addLine("<script type=\"text/javascript\">");
		jg.addLine("var QxSettings = {");
		jg.addLine("imageCorePath : \"images\",");
		jg.addLine("imageIconPath : \"themes/icons\",");
		jg.addLine("imageWidgetPath : \"themes/widgets\"");
		jg.addLine("};");
		jg.addLine("</script>");
		jg
				.addLine("<script type=\"text/javascript\" src=\"script/qooxdoo.js\"></script>");
		jg
				.addLine("<script type=\"text/javascript\" src=\"calendar/scw.js\"></script>");
		jg.addLine("</head><body>");
		jg.addLine("<script type=\"text/javascript\">");
		jg.addLine("window.application.main = function() {");
		jg.addLine("doc = this.getClientWindow().getClientDocument();");
		loading = new Loading("Loading...");
		ComponentManager.get().addComponent(loading);
		JsGenerator.get().addLine("doc.add(" + loading.getVarName() + ");");
		// JsGenerator.addLine("app = new QxApplication()");
		// JsGenerator.addLine("app.init();");
		// JsGenerator.addLine("win = app.getClientWindow();");
		// JsGenerator.addLine("doc = win.getClientDocument();");
		// JsGenerator.addLine("ajaxWin = new QxWindow(\"Requesting
		// server\");");
		// JsGenerator.addLine("ajaxWin.setModal(true);");
		// JsGenerator.addLine("ajaxWin.setShowClose(false);");
		// JsGenerator.addLine("ajaxWin.setShowMaximize(false);");
		// JsGenerator.addLine("ajaxWin.setShowMinimize(false);");
		// JsGenerator.addLine("ajaxWin.setMoveable(false);");
		// JsGenerator.addLine("ajaxWin.setResizeable(false);");
		// JsGenerator.addLine("ajaxWin.setShowIcon(false);");
		// JsGenerator
		// .addLine("ajaxWin.add(new QxAtom(\"Loading ... please wait.\"));");
		// JsGenerator.addLine("doc.add(ajaxWin);");
	}

	protected String getCode() {
		JsGenerator jg = JsGenerator.get();
		jg.addLine("function clickEvent() {");
		loading.setVisibility(true);
		jg.addLine("var req = new QxRequest(\"" + servlet
				+ "/clickEvent\", QxConst.METHOD_GET, QxConst.MIMETYPE_TEXT);");
		jg.addLine("req.setAsynchronous(true);");
		jg
				.addLine("req.setRequestHeader(\"Content-Type\", \"application/x-www-form-urlencoded\");");
		jg.addLine("req.setProhibitCaching(true);");
		jg.addLine("req.setParameter(\"id\", this.id);");
		jg.addLine("req.addEventListener(\"completed\", function(e) {");
		jg.addLine("eval(e.getData().getContent());");
		loading.setVisibility(false);
		jg.addLine("QxWidget.flushGlobalQueues();");
		jg.addLine("});");
		jg.addLine("req.send();");
		jg.addLine("};");

		jg.addLine("function checkedChangedEvent() {");
		loading.setVisibility(true);
		jg
				.addLine("var req = new QxRequest(\""
						+ servlet
						+ "/checkedChangedEvent\", QxConst.METHOD_GET, QxConst.MIMETYPE_TEXT);");
		jg.addLine("req.setAsynchronous(true);");
		jg
				.addLine("req.setRequestHeader(\"Content-Type\", \"application/x-www-form-urlencoded\");");
		jg.addLine("req.setProhibitCaching(true);");
		jg.addLine("req.setParameter(\"id\", this.id);");
		jg.addLine("req.setParameter(\"checked\", this.getChecked());");
		jg.addLine("req.addEventListener(\"completed\", function(e) {");
		jg.addLine("eval(e.getData().getContent());");
		loading.setVisibility(false);
		jg.addLine("QxWidget.flushGlobalQueues();");
		jg.addLine("});");
		jg.addLine("req.send();");
		jg.addLine("};");

		jg.addLine("function selectionChangedEvent() {");
		loading.setVisibility(true);
		jg
				.addLine("var req = new QxRequest(\""
						+ servlet
						+ "/selectionChangedEvent\", QxConst.METHOD_GET, QxConst.MIMETYPE_TEXT);");
		jg.addLine("req.setAsynchronous(true);");
		jg
				.addLine("req.setRequestHeader(\"Content-Type\", \"application/x-www-form-urlencoded\");");
		jg.addLine("req.setProhibitCaching(true);");
		jg.addLine("req.setParameter(\"id\", this.id);");
		jg.addLine("req.setParameter(\"selected\", this.getSelected().id);");
		jg.addLine("req.addEventListener(\"completed\", function(e) {");
		jg.addLine("eval(e.getData().getContent());");
		loading.setVisibility(false);
		jg.addLine("QxWidget.flushGlobalQueues();");
		jg.addLine("});");
		jg.addLine("req.send();");
		jg.addLine("};");

		jg.addLine("function textChangedEvent() {");
		loading.setVisibility(true);
		jg
				.addLine("var req = new QxRequest(\""
						+ servlet
						+ "/textChangedEvent\", QxConst.METHOD_GET, QxConst.MIMETYPE_TEXT);");
		jg.addLine("req.setAsynchronous(true);");
		jg
				.addLine("req.setRequestHeader(\"Content-Type\", \"application/x-www-form-urlencoded\");");
		jg.addLine("req.setProhibitCaching(true);");
		jg.addLine("req.setParameter(\"id\", this.id);");
		jg.addLine("req.setParameter(\"text\", this.getValue());");
		jg.addLine("req.addEventListener(\"completed\", function(e) {");
		jg.addLine("eval(e.getData().getContent());");
		loading.setVisibility(false);
		jg.addLine("QxWidget.flushGlobalQueues();");
		jg.addLine("});");
		jg.addLine("req.send();");
		jg.addLine("};");

		jg.addLine("function treeSelectionChangedEvent(e) {");
		loading.setVisibility(true);
		jg
				.addLine("var req = new QxRequest(\""
						+ servlet
						+ "/treeSelectionChangedEvent\", QxConst.METHOD_GET, QxConst.MIMETYPE_TEXT);");
		jg.addLine("req.setAsynchronous(true);");
		jg
				.addLine("req.setRequestHeader(\"Content-Type\", \"application/x-www-form-urlencoded\");");
		jg.addLine("req.setProhibitCaching(true);");
		//jg.addLine("alert(e.getData().getFirst());");
		jg.addLine("req.setParameter(\"id\", e.getData().getFirst().id);");
		jg.addLine("req.setParameter(\"text\", e.getData().getFirst()._labelObject.getHtml());");
		jg.addLine("req.addEventListener(\"completed\", function(e) {");
		jg.addLine("eval(e.getData().getContent());");
		loading.setVisibility(false);
		jg.addLine("QxWidget.flushGlobalQueues();");
		jg.addLine("});");
		jg.addLine("req.send();");
		jg.addLine("};");

		
		jg.addLine("function listViewSelectionChangedEvent() {");
		loading.setVisibility(true);
		jg
				.addLine("var req = new QxRequest(\""
						+ servlet
						+ "/listViewSelectionChangedEvent\", QxConst.METHOD_GET, QxConst.MIMETYPE_TEXT);");
		jg.addLine("req.setAsynchronous(true);");
		jg
				.addLine("req.setRequestHeader(\"Content-Type\", \"application/x-www-form-urlencoded\");");
		jg.addLine("req.setProhibitCaching(true);");
		jg
				.addLine("req.setParameter(\"id\", this.getBoundedWidget().getView().id);");
		jg
				.addLine("req.setParameter(\"selected\", this.getBoundedWidget().getRelativeItemPosition(this.getSelectedItem()));");
		jg.addLine("req.addEventListener(\"completed\", function(e) {");
		jg.addLine("eval(e.getData().getContent());");
		loading.setVisibility(false);
		jg.addLine("QxWidget.flushGlobalQueues();");
		jg.addLine("});");
		jg.addLine("req.send();");
		jg.addLine("};");

		jg.addLine("function dateChangedEvent(control) {");
		loading.setVisibility(true);
		jg
				.addLine("var req = new QxRequest(\""
						+ servlet
						+ "/dateChangedEvent\", QxConst.METHOD_GET, QxConst.MIMETYPE_TEXT);");
		jg.addLine("req.setAsynchronous(true);");
		jg
				.addLine("req.setRequestHeader(\"Content-Type\", \"application/x-www-form-urlencoded\");");
		jg.addLine("req.setProhibitCaching(true);");
		jg.addLine("req.setParameter(\"id\", control.id);");
		// jg.addLine("req.setParameter(\"date\",
		// control.getHtmlProperty(\"value\"));");
		jg
				.addLine("req.setParameter(\"date\", document.getElementById(control.id).value);");
		jg.addLine("req.addEventListener(\"completed\", function(e) {");
		jg.addLine("eval(e.getData().getContent());");
		loading.setVisibility(false);
		jg.addLine("QxWidget.flushGlobalQueues();");
		jg.addLine("});");
		jg.addLine("req.send();");
		jg.addLine("};");

		jg.addLine("}");
		jg.addLine("</script>");
		jg.addLine("</body></html>");
		return jg.getCode();
	}

}
