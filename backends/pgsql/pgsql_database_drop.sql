-- psql -U wzdftpd -f pgsql_database_drop.sql wzdftpd

--
-- Use this to completely destroy wzdftpd
--

-- Removing privileges
-- REVOKE ALL ON *.* FROM "wzdftpd"@"localhost";

-- Deleting user ...
-- DELETE FROM mysql.user WHERE User='wzdftpd';

-- Droping database and all the tables in it
DROP DATABASE wzdftpd;

DROP USER wzdftpd;
