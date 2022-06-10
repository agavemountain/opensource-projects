# Ansible Playbooks
This directory contains some ansible playbooks to automate
some basic tasks required to maintain a network/cluster of 
computing devices.

Modify the invetory/hosts file to contain the host names or IP
addresses of the devices.

## Ping the devices:
```bash
ansible -i ./invetory/hosts ubuntu -m ping --user <username> --ask-pass 
```
## Executing playbook:
```bash
ansible-playbook ./playbooks/<playbook.yml> --user <username> --ask-pass --ask-become-pass -i ./invetory/hosts ubuntu
```

**Context: [main](../README.md) / ansible**

+ **[update APT respositories](playbooks/apt.yml)**: Update apt repositories on each of the servers.
