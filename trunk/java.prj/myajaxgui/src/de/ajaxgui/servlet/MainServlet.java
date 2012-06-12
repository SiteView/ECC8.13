package de.ajaxgui.servlet;

import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.Hashtable;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.http.HttpSessionBindingEvent;
import javax.servlet.http.HttpSessionBindingListener;

import de.ajaxgui.Application;
import de.ajaxgui.ImageStream;
import de.ajaxgui.ext.ComponentManager;
import de.ajaxgui.ext.Event;
import de.ajaxgui.ext.EventManager;
import de.ajaxgui.ext.JsGenerator;
import de.ajaxgui.ext.Singleton;
import de.ajaxgui.ext.ThreadManager;

public class MainServlet extends HttpServlet implements
		HttpSessionBindingListener {

	private String mainclass = "";

	public void destroy() {

	}

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		HttpSession session = request.getSession();
		// PrintWriter out = response.getWriter();
		ServletOutputStream out = response.getOutputStream();

		// String[] path = request.getPathInfo().split("/");
		String url = request.getRequestURL().toString();
		// System.out.println(url);
		String[] urlSplit = url.split("/");
		String servlet = urlSplit[urlSplit.length - 1];
		// System.out.println(servlet);
		String path = request.getPathInfo();
		// System.out.println(path);

		if (path == null) {
			response.setContentType("text/html");
			if (session.getAttribute("mainclass") != null) {
				if (session.isNew()) {
					ThreadManager tm = (ThreadManager) session
							.getAttribute("tm");
					Thread appThread = tm.getApplicationThread();
					appThread.interrupt();
					session.invalidate();
				}
			}
			Class cl;
			try {
				cl = Class.forName(mainclass);
				Constructor c;
				try {
					c = cl.getConstructor();
					Application app;
					try {
						JsGenerator jg = new JsGenerator();
						JsGenerator.set(jg);
						ComponentManager cm = new ComponentManager();
						cm.setServletURI(servlet);
						ComponentManager.set(cm);
						session.setAttribute("cm", cm);
						ThreadManager tm = new ThreadManager();
						session.setAttribute("tm", tm);
						EventManager em = new EventManager();
						session.setAttribute("em", em);
						Hashtable<Class, Singleton> singletonHt = new Hashtable<Class, Singleton>();
						session.setAttribute("sht", singletonHt);
						InitCode ic = new InitCode();
						app = (Application) c.newInstance();
						session.setAttribute("mainclass", app);
						tm.setApplicationThread(app);
						Thread servletThread = Thread.currentThread();
						tm.setServletThread(servletThread);
						ThreadManager.set(tm);
						app.setup(jg, cm, tm, em, singletonHt);
						app.start();
						try {
							synchronized (servletThread) {
								servletThread.wait();
							}
							out.println(ic.getCode());
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					} catch (InstantiationException e) {
						e.printStackTrace();
					} catch (IllegalAccessException e) {
						e.printStackTrace();
					} catch (IllegalArgumentException e) {
						e.printStackTrace();
					} catch (InvocationTargetException e) {
						e.printStackTrace();
					}
				} catch (NoSuchMethodException e) {
					e.printStackTrace();
				}
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			}
		} else {
			response.setContentType("text/plain");

			JsGenerator jg = new JsGenerator();
			JsGenerator.set(jg);
			ComponentManager cm = (ComponentManager) session.getAttribute("cm");
			ThreadManager tm = (ThreadManager) session.getAttribute("tm");
			Thread servletThread = Thread.currentThread();
			tm.setServletThread(servletThread);
			EventManager em = (EventManager) session.getAttribute("em");
			Hashtable<Class, Singleton> singletonHt = (Hashtable<Class, Singleton>) session
					.getAttribute("sht");
			Application app = (Application) session.getAttribute("mainclass");
			app.setup(jg, cm, tm, em, singletonHt);

			if (request.getParameter("id") != null) {
				int id = Integer.parseInt(request.getParameter("id"));
				if (path.equals("/clickEvent")) {
					Event e = new Event(Event.Type.CLICK);
					e.setComponentId(id);
					em.addEvent(e);
					switchThread(tm);
					out.println(jg.getCode());
				} else if (path.equals("/checkedChangedEvent")) {
					if (request.getParameter("checked") != null) {
						boolean checked = false;
						if (request.getParameter("checked").equals("true"))
							checked = true;
						else if (request.getParameter("checked")
								.equals("false"))
							checked = false;
						Event e = new Event(Event.Type.CHECKEDCHANGED);
						e.setComponentId(id);
						e.setData(checked);
						em.addEvent(e);
						switchThread(tm);
						out.println(jg.getCode());
					}
				} else if (path.equals("/selectionChangedEvent")) {
					if (request.getParameter("selected") != null) {
						int selected = Integer.parseInt(request
								.getParameter("selected"));
						Event e = new Event(Event.Type.SELECTIONCHANGED);
						e.setComponentId(id);
						e.setData(selected);
						em.addEvent(e);
						switchThread(tm);
						out.println(jg.getCode());
					}
				} else if (path.equals("/textChangedEvent")) {
					if (request.getParameter("text") != null) {
						String text = request.getParameter("text");
						Event e = new Event(Event.Type.TEXTCHANGED);
						e.setComponentId(id);
						e.setData(text);
						em.addEvent(e);
						switchThread(tm);
						out.println(jg.getCode());
					}
				} else if (path.equals("/listViewSelectionChangedEvent")) {
					if (request.getParameter("selected") != null) {
						int selected = Integer.parseInt(request
								.getParameter("selected"));
						Event e = new Event(Event.Type.LISTVIEWSELECTIONCHANGED);
						e.setComponentId(id);
						e.setData(selected);
						em.addEvent(e);
						switchThread(tm);
						out.println(jg.getCode());
					}
				} else if (path.equals("/treeSelectionChangedEvent")) {
					Event e = new Event(Event.Type.TREESELECTIONCHANGED);
					e.setComponentId(id);
					String text = request.getParameter("text");
					e.setData(text);
					em.addEvent(e);
					switchThread(tm);
					out.println(jg.getCode());
				} else if (path.equals("/imageStream")) {
					Object obj = cm.getComponent(id);
					if (obj instanceof ImageStream) {
						ImageStream is = (ImageStream) obj;
						switch (is.getFormat()) {
						case JPEG:
							response.setContentType("image/jpeg");
							break;
						case PNG:
							response.setContentType("image/png");
							break;
						}
						out.write(is.getImage());
					}
				} else if (path.equals("/dateChangedEvent")) {
					if (request.getParameter("date") != null) {
						String date = request.getParameter("date");
						Event e = new Event(Event.Type.DATECHANGED);
						e.setComponentId(id);
						e.setData(date);
						em.addEvent(e);
						switchThread(tm);
						out.println(jg.getCode());
					}
				} else {
					out.println("Sorry, wrong url path!<br>");
					out.println(url);
				}
			}
		}
	}

	private void switchThread(ThreadManager tm) {
		Thread servletThread = tm.getServletThread();
		Thread appThread = tm.getApplicationThread();
		synchronized (appThread) {
			appThread.notify();
		}
		try {
			synchronized (servletThread) {
				servletThread.wait();
			}
		} catch (InterruptedException ie) {
			ie.printStackTrace();
		}
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doGet(request, response);
	}

	public void init(ServletConfig config) throws ServletException {
		super.init(config);
		mainclass = config.getInitParameter("mainclass");
	}

	public void valueBound(HttpSessionBindingEvent event) {
	}

	public void valueUnbound(HttpSessionBindingEvent event) {
		Object obj = event.getValue();
		if (obj instanceof ThreadManager) {
			ThreadManager tm = (ThreadManager) obj;
			Thread appThread = tm.getApplicationThread();
			appThread.interrupt();
		}
	}
}
