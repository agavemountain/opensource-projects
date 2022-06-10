; schema sample

; more remarks

#schema CBS

#dictionary
    CLIENT_NO, Z,    5
    CLIENT_NAME,    A  ,    25
    ADDRESS,        A,  25
    PHONE,          N, 10, "(___)___-____"
#end dictionary

; file specifications
#file CLIENTS
    CLIENT_NO
    CLIENT_NAME
    ADDRESS
    PHONE
#end file

; index specifications

#key CLIENTS CLIENT_NO

#end schema CBS

