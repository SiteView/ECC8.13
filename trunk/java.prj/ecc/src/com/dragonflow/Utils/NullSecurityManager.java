/*
 * Created on 2005-2-9 3:06:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Utils;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

public class NullSecurityManager extends java.lang.SecurityManager {

    public void checkPermission(java.security.Permission permission, java.lang.Object obj) {
    }

    public void checkRead(java.lang.String s, java.lang.Object obj) {
    }

    public void checkConnect(java.lang.String s, int i, java.lang.Object obj) {
    }

    public void checkPermission(java.security.Permission permission) {
    }

    public void checkMulticast(java.net.InetAddress inetaddress) {
    }

    public void checkAccess(java.lang.ThreadGroup threadgroup) {
    }

    public void checkConnect(java.lang.String s, int i) {
    }

    public void checkAccess(java.lang.Thread thread) {
    }

    public NullSecurityManager() {
    }

    public void checkAwtEventQueueAccess() {
    }

    public void checkCreateClassLoader() {
    }

    public void checkPrintJobAccess() {
    }

    public void checkPropertiesAccess() {
    }

    public void checkSetFactory() {
    }

    public void checkSystemClipboardAccess() {
    }

    public void checkExit(int i) {
    }

    public void checkListen(int i) {
    }

    public void checkRead(java.io.FileDescriptor filedescriptor) {
    }

    public void checkWrite(java.io.FileDescriptor filedescriptor) {
    }

    public void checkMemberAccess(java.lang.Class class1, int i) {
    }

    public boolean checkTopLevelWindow(java.lang.Object obj) {
        return true;
    }

    public void checkDelete(java.lang.String s) {
    }

    public void checkExec(java.lang.String s) {
    }

    public void checkLink(java.lang.String s) {
    }

    public void checkPackageAccess(java.lang.String s) {
    }

    public void checkPackageDefinition(java.lang.String s) {
    }

    public void checkPropertyAccess(java.lang.String s) {
    }

    public void checkRead(java.lang.String s) {
    }

    public void checkSecurityAccess(java.lang.String s) {
    }

    public void checkWrite(java.lang.String s) {
    }

    public void checkAccept(java.lang.String s, int i) {
    }
}
