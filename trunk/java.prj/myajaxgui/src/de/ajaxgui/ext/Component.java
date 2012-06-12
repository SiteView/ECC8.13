package de.ajaxgui.ext;

public class Component {
	private int id = 0;

	public Component() {
		this.id = ComponentManager.get().getNextId();
	}

	public int getId() {
		return id;
	}

	public String getVarName() {
		return "v" + id;
	}
}
