; $Id$
;
; Dropbox Uploader makefile
; ----------------
; This makefile downloads the lastest version from Dropbox Uploader and 
; places it sites/all/libraries/DropboxUploader.

core = 7.x
api = 2

libraries[DropboxUploader][download][type] = "get"
libraries[DropboxUploader][download][url] = "https://github.com/BenTheDesigner/Dropbox/archive/master.zip"
libraries[DropboxUploader][directory_name] = "dropbox"
libraries[DropboxUploader][destination] = "libraries"