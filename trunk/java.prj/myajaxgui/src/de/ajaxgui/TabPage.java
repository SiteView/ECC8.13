package de.ajaxgui;

import java.util.Hashtable;

import de.ajaxgui.ext.ComponentManager;
import de.ajaxgui.ext.JsGenerator;

public class TabPage extends AbstractButton {

	protected TabControl control = null;

	private Hashtable<Integer, Control> controls = new Hashtable<Integer, Control>();

	public TabPage(String text) {
		super(text);
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxTabViewButton(\"" + text + "\");");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
		jg.addLine(getVarName()
				+ ".addEventListener(QxConst.EVENT_TYPE_CLICK, clickEvent);");
		jg.addLine("new QxTabViewPage(" + getVarName() + ");");
	}

	public void add(Control component) {
		controls.put(component.getId(), component);
		ComponentManager.get().addComponent(component);
		JsGenerator.get().addLine(
				getVarName() + ".getPage().add(" + component.getVarName()
						+ ");");
	}

	public void addClick(Object o, String func) {
		clickObject.add(o);
		clickFunc.add(func);
	}
}
