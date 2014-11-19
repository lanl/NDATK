%  ========================================================================  %
% 
%       Author: Mark G. Gray
%       Date:   Tue Dec 24 15:39:45 MST 2002
% 
%       Copyright (c) 2002 Mark G. Gray. All rights reserved.
% 
%       $Id: context.mp,v 1.1 2008/07/10 21:43:12 mgg Exp $
% 
%  ========================================================================  %

% Macros to draw Jackson's Context Diagrams
% See: M. Jackson, "Problem Frames"

def twobar(suffix a) =		% draw two 1 pt bars on left side of box
  draw a.nw -- a.nw - (1, 0) -- a.sw - (1, 0) -- a.sw;
  draw a.nw -- a.nw - (2, 0) -- a.sw - (2, 0) -- a.sw;
enddef;

def onebar(suffix a) =		% draw one 1pt bar on left side of box
  draw a.nw -- a.nw - (1, 0) -- a.sw - (1, 0) -- a.sw;
enddef;

def drawdashedboxed(text t) =	% Draw each box dashed
  fixsize(t); fixpos(t);
  forsuffixes s=t: draw pic_mac_.s; draw bpath.s dashed evenly; endfor
enddef;

%  ========================================================================  %
