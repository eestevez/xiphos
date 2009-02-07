;;
;;  en.nsh
;;
;;  Default language strings for the Xiphos NSIS installer.
;;
;;  Version 2
;;

;--------------------------------
; Uninstall Log

LangString UNLOG_HEADER ${LANG_ENGLISH} \
    "=========== Uninstaller Log please do not edit this file ==========="
LangString UNLOG_DAT_NOT_FOUND ${LANG_ENGLISH} \
    "${UNINST_DAT} not found, unable to perform uninstall."
LangString UNLOG_DEL_FILE ${LANG_ENGLISH} 'Delete File "$R9"?'
LangString UNLOG_DEL_DIR ${LANG_ENGLISH} 'Delete Directory "$R9"?'
LangString UNLOG_EMPTY_DIR ${LANG_ENGLISH} \
    "Previous installation detected at $0.$\n\
    Required file ${UNINSTALL_LOG}.dat is missing.$\n$\n\
    It is highly recommended to select an \
    empty directory and perform a fresh \
    installation."
LangString UNLOG_ERROR_LOG ${LANG_ENGLISH} "Error in log ${UNINSTALL_LOG}."
LangString UNLOG_ERROR_CREATE ${LANG_ENGLISH} "Error creating ${UNINSTALL_LOG}."


;--------------------------------
; Text for page with release notes

!insertmacro ReadmeLangStrings "" "${LANG_ENGLISH}" \
    "Release Notes" \
    "Please review the following important information." \
    "About $(^name):" \
    "$\n  Click on scrollbar arrows or press Page Down to review the entire text."

