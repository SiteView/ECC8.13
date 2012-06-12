package de.ajaxgui;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Collection;

import de.ajaxgui.ext.JsGenerator;

public class ListView extends Control {

	private ListViewHeader listViewHeader = null;

	public ArrayList<ListViewItem> listViewItems = new ArrayList<ListViewItem>();

	private ArrayList<String> selectionChangedFunc = new ArrayList<String>();

	private ArrayList<Object> selectionChangedObject = new ArrayList<Object>();

	public ListViewItem selected = null;

	public ListView(ListViewHeader lvh) {
		this.listViewHeader = lvh;
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxListView([]," + lvh.getVarName()
				+ ");");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
		jg.addLine(getVarName() + ".setBorder(QxBorderObject.presets.shadow);");
		jg.addLine(getVarName() + ".setBackgroundColor(\"white\");");
		jg.addLine(getVarName()
				+ ".getPane().getManager().setMultiSelection(false);");
		jg
				.addLine(getVarName()
						+ ".getPane().getManager().addEventListener(\"changeSelection\",listViewSelectionChangedEvent);");
	}

	public void add(ListViewItem lvi) {
		addIntern(lvi);
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + ".updateSort();");
		jg.addLine(getVarName() + ".update();");
	}

	public void add(Collection<ListViewItem> lvis) {
		for (ListViewItem lvi : lvis) {
			addIntern(lvi);
		}
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + ".updateSort();");
		jg.addLine(getVarName() + ".update();");
	}

	private void addIntern(ListViewItem lvi) {
		listViewItems.add(lvi);
		// ComponentManagerThread.get().addComponent(lvi);
		if (lvi.getCode().size() == 0)
			return;
		JsGenerator jg = JsGenerator.get();
		jg.add(getVarName() + ".getData().push({");
		int index = -1;
		for (int i = 0; i < lvi.getCode().size() - 1; i++) {
			index = i;
			if (i == listViewHeader.getColumns().size())
				break;
			jg.add((String) listViewHeader.getColumns().get(i) + ":"
					+ (String) lvi.getCode().get(i) + ",");
		}
		index++;
		jg.add((String) listViewHeader.getColumns().get(index) + ":"
				+ (String) lvi.getCode().get(index));
		jg.addLine("});");
	}

	public void addSelectionChanged(Object o, String func) {
		selectionChangedObject.add(o);
		selectionChangedFunc.add(func);
	}

	public void clear() {
		listViewItems.clear();
		selected = null;
		JsGenerator jg = JsGenerator.get();
		jg.add(getVarName() + ".getData().removeAll();");
		jg.addLine(getVarName() + ".updateSort();");
		jg.addLine(getVarName() + ".update();");
	}

	public void doSelectionChanged() {
		for (int i = 0; i < selectionChangedObject.size(); i++) {
			Object obj = selectionChangedObject.get(i);
			String func = selectionChangedFunc.get(i);
			Class cl = obj.getClass();
			Method m;
			try {
				m = cl.getMethod(func, new Class[] {});
				try {
					m.invoke(obj);
				} catch (IllegalArgumentException e) {
					e.printStackTrace();
				} catch (InvocationTargetException e) {
					e.printStackTrace();
				} catch (IllegalAccessException e) {
					e.printStackTrace();
				}
			} catch (SecurityException e) {
				e.printStackTrace();
			} catch (NoSuchMethodException e) {
				e.printStackTrace();
			}
		}
	}

	public ListViewItem getSelected() {
		return selected;
	}
}
