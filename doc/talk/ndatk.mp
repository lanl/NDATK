verbatimtex
\documentclass{article}
\usepackage{color}
\definecolor{grey}{rgb}{0.8,0.8,0.8}
\begin{document}
\tiny
etex

input boxes;
input context;

beginfig(10);			% ndatk Commanded Information Problem Frame

  boxit.uc(btex \begin{minipage}{.5in} \centering
    User Code \end{minipage} etex);
  boxit.ud(btex \begin{minipage}{.5in} \centering
    User Data \end{minipage} etex);
  circleit.r(btex \begin{minipage}{.5in} \centering
    $\mathrm{R} \Rightarrow \mathrm{UD} \sim \mathrm{ND}
    \wedge \mathrm{status}$ \end{minipage} etex);

  uc.c = (2.0*72, 2.5*72);
  ud.c = (2.0*72, 1.5*72);
  r.c = (3.0*72, 1.5*72);
  r.dx = r.dy;

  drawboxed(uc, ud);
  drawdashedboxed(r);

  boxit.ndi(btex \begin{minipage}{.2in} \centering
    ndatk \end{minipage} etex);
  boxjoin(a.se=b.ne; a.sw=b.nw);
  boxit.api(btex \begin{minipage}{.5in} \centering
    API \end{minipage} etex);
  boxit.fsm(btex \begin{minipage}{.5in} \centering
    FSM \end{minipage} etex);
  boxit.rdr(btex \begin{minipage}{.5in} \centering
    Readers \end{minipage} etex);
  boxit.utils(btex \begin{minipage}{.5in} \centering
    Utilities \end{minipage} etex);

  api.c = (1.0*72, 1.5*72);
  ndi.sw = api.nw;
  drawdashedboxed(ndi, api, fsm, rdr, utils);
  draw api.nw -- ndi.nw -- ndi.ne -- ndi.se --
  api.ne -- utils.se -- utils.sw -- cycle;

  boxjoin(a.se=b.ne; a.sw=b.nw);
  boxit.g(btex \begin{minipage}{.5in} \centering
    Exsdir \end{minipage} etex);
  boxit.sn(btex \begin{minipage}{.5in} \centering
    xsdir \end{minipage} etex);
  boxit.tn(btex \begin{minipage}{.5in} \centering
    Library \end{minipage} etex);
  boxit.pd(btex \begin{minipage}{.5in} \centering
    Chart \end{minipage} etex);

  sn.c = (2.0*72, 0.5*72);

  fill bpath sn withcolor (1.0, 0.5, 0.5);
  fill bpath tn withcolor (0.8, 0.8, 0.8);
  fill bpath pd withcolor (0.5, 1.0, 0.5);

  drawboxed(g, sn, tn, pd);
  
  draw api.e -- uc.w;
  label.lft(btex UC!R etex,
    point .5 * length (api.e -- uc.w) of (api.e -- uc.w));

  draw api.e -- ud.w;
  label.top(btex ndatk!UD etex,
    point .5 * length(api.e -- ud.w) of (api.e -- ud.w));

  draw rdr.e -- g.w;
  draw rdr.e -- sn.w;
  draw rdr.e -- tn.w;
  draw rdr.e -- pd.w;

  label.lft(btex ndatk!ND etex,
    point 0.5 * length(rdr.e -- pd.w) of (rdr.e -- pd.w));

  draw r.w -- g.e dashed evenly;
  draw r.w -- sn.e dashed evenly;
  draw r.w -- tn.e dashed evenly;
  draw r.w -- pd.e dashed evenly;
  label.rt(btex ND etex, point .5 * length (r.w -- pd.e) of (r.w -- pd.e));

  drawarrow r.w -- ud.e dashed evenly;
  label.top(btex UD etex, point .5 * length (r.w -- ud.e) of (r.w -- ud.e));
  draw r.w -- uc.e dashed evenly;
  label.rt(btex R etex, point .5 * length (r.w -- uc.ne) of (r.w -- uc.ne));

endfig;				% ndatk Commanded Information Problem Frame

end.
