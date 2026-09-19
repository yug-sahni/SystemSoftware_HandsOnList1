/*
 * ./19b &
kill -STOP <pid>
ps -o pid,stat,cmd -p <pid>     # STAT shows T
kill -CONT <pid>
ps -o pid,stat,cmd -p <pid>     # STAT goes back to S
*/
