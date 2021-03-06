-- psql -U wzdftpd -f pgsql_tables_create.sql wzdftpd

--
-- Table structure for table `ugroups`
--
CREATE TABLE groups (
  ref serial PRIMARY KEY,
  groupname varchar(255) UNIQUE NOT NULL,
  gid serial UNIQUE,
  defaultpath varchar(255) NOT NULL,
  flags varchar(32) default NULL,
  tagline varchar(255) DEFAULT NULL,
  groupperms integer default NULL,
  max_idle_time integer default NULL,
  num_logins integer default NULL,
  max_ul_speed bigint NULL,
  max_dl_speed bigint NULL,
  ratio integer NULL
);

--
-- Dumping data for table `groups`
--

INSERT INTO groups (groupname,gid,defaultpath,tagline) VALUES ('admin',nextval('groups_gid_seq'),'/','admin group');


--
-- Table structure for table `users`
--

CREATE TABLE users (
  ref serial PRIMARY KEY,
  username varchar(255) NOT NULL,
  userpass varchar(48) default NULL,
  rootpath varchar(255) NOT NULL,
  tagline varchar(255) default NULL,
  uid serial UNIQUE,
  creator integer default NULL,
  flags varchar(32) default NULL,
  max_idle_time integer  default NULL,
  max_ul_speed bigint default NULL,
  max_dl_speed bigint default NULL,
  num_logins integer default NULL,
  logins_per_ip integer default NULL,
  ratio integer default NULL,
  user_slots integer default NULL,
  leech_slots integer default NULL,
  perms bigint default NULL,
  credits bigint default NULL,
  last_login time default NULL
);

--
-- Dumping data for table `users`
--

INSERT INTO users (username,rootpath,tagline,uid,flags,perms) VALUES ('wzdftpd','/','local admin',nextval('users_uid_seq'),'OIstH',cast (X'ffffffff' as integer));

--
-- Table structure for table `UGR` (User-Group Relations)
--

CREATE TABLE ugr (
  uref integer NOT NULL,
  gref integer NOT NULL,
  PRIMARY KEY(uref,gref)
);

ALTER TABLE ONLY ugr ADD CONSTRAINT "$1" FOREIGN KEY (uref) REFERENCES users(ref);
ALTER TABLE ONLY ugr ADD CONSTRAINT "$2" FOREIGN KEY (gref) REFERENCES groups(ref);

--
-- Table structure for table `IP` (User/Group IPs)
--

CREATE TABLE groupip (
  ref integer NOT NULL,
  ip VARCHAR(255) NOT NULL,
  PRIMARY KEY(ref,ip)
);

ALTER TABLE ONLY groupip ADD CONSTRAINT "$1" FOREIGN KEY (ref) REFERENCES groups(ref);

--
-- Table structure for table `IP` (User/Group IPs)
--

CREATE TABLE userip (
  ref integer NOT NULL,
  ip VARCHAR(255) NOT NULL,
  PRIMARY KEY(ref,ip)
);

ALTER TABLE ONLY userip ADD CONSTRAINT "$1" FOREIGN KEY (ref) REFERENCES users(ref);

INSERT into userip (ref,ip) SELECT users.ref,'127.0.0.1' FROM users WHERE users.uid=1;

--
-- Table structure for table `Stats`
--

CREATE TABLE stats (
  ref serial NOT NULL,
  bytes_ul_total bigint default 0,
  bytes_dl_total bigint default 0,
  files_ul_total integer default 0,
  files_dl_total integer default 0,
  PRIMARY KEY(ref)
);

ALTER TABLE ONLY stats ADD CONSTRAINT "$1" FOREIGN KEY (ref) REFERENCES users(ref);

INSERT INTO stats (ref) SELECT users.ref FROM users where uid=1;

--
-- hmm - moo, moo; I'm trying to insert references into UGR
--
INSERT into ugr (uref,gref) SELECT users.ref,groups.ref FROM users,groups WHERE users.uid=1 AND groups.gid=1;

--
-- find all groups (gid) given a uid
--   select gid from groups,users,UGR where users.uid=1 and users.ref=UGR.uref and groups.ref=UGR.gref;
--
-- find all infos given a uid (not very usable)
--   select * from groups,users,UGR,UserIP where users.uid=1 and users.ref=UGR.uref and groups.ref=UGR.gref AND UserIP.ref=users.ref;
--
-- find all ip for a user
--   select UserIP.ip from UserIP,users where users.ref=1 AND users.ref=UserIP.ref;
--
--
-- reset auto-increment: ALTER TABLE users AUTO_INCREMENT=4;
--
