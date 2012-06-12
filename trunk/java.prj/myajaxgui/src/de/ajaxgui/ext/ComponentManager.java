package de.ajaxgui.ext;

import java.util.Hashtable;

public class ComponentManager {
	private static final ThreadLocal<ComponentManager> componentManager = new ThreadLocal<ComponentManager>();

	public static ComponentManager get() {
		return componentManager.get();
	}

	public static void set(ComponentManager cm) {
		componentManager.set(cm);
	}

	private Hashtable<Integer, Component> components = new Hashtable<Integer, Component>();

	private int idCounter = 0;

	private String servletURI = "";

	public void addComponent(Component component) {
		components.put(component.getId(), component);
	}

	public Component getComponent(int id) {
		return components.get(id);
	}

	public int getNextId() {
		idCounter++;
		return idCounter - 1;
	}

	public String getServletURI() {
		return servletURI;
	}

	public void setServletURI(String servletURI) {
		this.servletURI = servletURI;
	}
}
