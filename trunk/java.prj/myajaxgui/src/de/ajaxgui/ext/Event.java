package de.ajaxgui.ext;

public class Event {
	public static enum Type {
		CLOSE, CLICK, CHECKEDCHANGED, SELECTIONCHANGED, TEXTCHANGED, LISTVIEWSELECTIONCHANGED, DATECHANGED,TREESELECTIONCHANGED
	}

	private Object data = null;

	private int componentId = -1;

	private Type type;

	public Event(Type type) {
		this.type = type;
	}

	public Object getData() {
		return data;
	}

	public void setData(Object data) {
		this.data = data;
	}

	public Type getType() {
		return type;
	}

	public int getComponentId() {
		return componentId;
	}

	public void setComponentId(int componentId) {
		this.componentId = componentId;
	}
}
