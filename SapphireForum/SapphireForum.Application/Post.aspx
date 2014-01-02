<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Post.aspx.cs" Inherits="SapphireForum.Application.Post" MaintainScrollPositionOnPostback="true" %>
<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">

    <style type="text/css">
        
        /* duplicated */
        .blue {
            color: #0088CC;
        }

        /* duplicated with other id */
        #DataPagerComments {
            display: block;
            margin-top: 20px;
            text-align: center;
        }

        .comments-list {
            list-style: none;
        }

        .comments-list li {
            margin: 10px 0;
            padding: 10px;
            border: 1px solid #CCC;
            border-radius: 10px;
            background-color: #EEEEEE;
        }

        .user-avatar {
            margin: 5px;
            border-radius: 8px;
        }

        #main-comment {
            border-color: #aaa;
            background-color: #ccc;
        }

        .bubble-content {
            position:relative;
            float:left;
            min-height: 100px;
            margin: 10px 0 10px 12px;
            width: 700px;
            padding:10px 20px;
            border-radius:10px;
            background-color:#FFF;
            box-shadow:2px 3px 5px rgba(0,0,0,.4);
            word-wrap: break-word;
        }

        .bubble-point {
            border-top:10px solid transparent;
            border-bottom:10px solid transparent;
            border-right: 12px solid #FFF;
            position:absolute;
            left:-12px;
            top:12px;
        }

        .new-comment-text {
            display: block;
            width: 100%;
            height: 100%;
        }
        
    </style>

    <asp:FormView ID="fvPosts" ItemType="SapphireForum.Application.Models.Post" DataKeyNames="Id" OnDataBound="fvPosts_DataBound"
        SelectMethod="fvPosts_GetItem" runat="server" RenderOuterTable="false">
        <HeaderTemplate>
            <header class="post-header">
                <h2 class="blue"><%#: Item.Title %></h2>
                <div>
                    <ul class="inline">
                        <li>
                            <span class="blue">Category</span>:
                            <a class="btn btn-mini" href="Posts.aspx?category=<%#: Item.Category.Name %>"><i class="icon-list"></i> <%#: Item.Category.Name %></a>
                        </li>
                        <asp:Repeater runat="server" DataSource="<%# Item.Tags %>" 
                            ItemType="SapphireForum.Application.Models.Tag">
                            <HeaderTemplate>
                                <li>
                                    <span class="blue">Tags:</span>
                                </li>
                            </HeaderTemplate>
                            <ItemTemplate>
                                <li><a class="btn btn-mini" href="Posts.aspx?tag=<%#: Item.Text %>"><i class="icon-tag"></i> <%#: Item.Text %></a></li>
                            </ItemTemplate>
                        </asp:Repeater>
                    </ul>
                </div>
                <hr />
            </header>
        </HeaderTemplate>
        <ItemTemplate>
                <ul class="comments-list">
                    <li id="main-comment">
                        <asp:HyperLink ID="EditLinkButton" CssClass="btn pull-right" NavigateUrl="~/Admin/Post?id=" runat="server" Text="Edit" Visible="false" />
                        <div class="media">
                            <div class="pull-left text-center">
                                <a class="btn btn-mini" href="Posts.aspx?user=<%#: Item.User.UserName %>"><i class="icon-user"></i> <%# Item.User.UserName %></a>
                                <img class="media-object user-avatar" src="Content/Images/default-avatar.png" width="80" height="80" />
                                <span class="blue"><%#: Item.PostDate.ToShortDateString() %><br /><%#: Item.PostDate.ToShortTimeString() %></span>
                            </div>
                            <div class="media-body">
                                <div class="media">
                                    <div class="bubble-content">
                                        <div class="bubble-point"></div>
                                        <p><%#: Item.Text %></p>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </li>
                </ul>
            </Itemtemplate>
        <EmptyDataTemplate>
            <div class="alert alert-error">Post not found. Maybe the post is already deleted.</div>
        </EmptyDataTemplate>
    </asp:FormView>

     <asp:ListView ID="CommentsList" ItemType="SapphireForum.Application.Models.Comment" runat="server" DataKeyNames="Id" 
        OnItemDataBound="CommentsList_ItemDataBound" OnItemEditing="CommentsList_ItemEditing"
        SelectMethod="CommentsList_GetData"
        UpdateMethod="CommentsList_UpdateItem"
        DeleteMethod="CommentsList_DeleteItem">
        <ItemTemplate>
            <li>
                <asp:LinkButton ID="DeleteLinkButton" CssClass="btn pull-right" runat="server" CommandName="Delete" Text="Delete" Visible="false" />
                <asp:LinkButton ID="EditLinkButton" CssClass="btn pull-right" runat="server" CommandName="Edit" Text="Edit" Visible="false" />
                <div class="media">
                    <div class="pull-left text-center">
                        <a class="btn btn-mini" href="Posts.aspx?user=<%#: Item.User.UserName %>"><i class="icon-user"></i> <%# Item.User.UserName %></a>
                        <img class="media-object user-avatar" src="Content/Images/default-avatar.png" width="80" height="80" />
                        <span class="blue"><%#: Item.PostDate.ToShortDateString() %><br /><%#: Item.PostDate.ToShortTimeString() %></span>
                    </div>
                    <div class="media-body">
                        <div class="media">
                            <div class="bubble-content">
                                <div class="bubble-point"></div>
                                <p><%#: Item.Text %></p>
                            </div>
                        </div>
                    </div>
                </div>
            </li>
        </ItemTemplate>
        <EditItemTemplate>
            <li>
                <asp:LinkButton ID="CancelLinkButton" CssClass="btn pull-right" runat="server" CommandName="Cancel" Text="Cancel" />
                <asp:LinkButton ID="UpdateLinkButton" CssClass="btn pull-right" runat="server" CommandName="Update" Text="Update" />
                <div class="media">
                    <div class="pull-left text-center">
                        <a class="btn btn-mini" href="Posts.aspx?user=<%#: Item.User.UserName %>"><i class="icon-user"></i> <%# Item.User.UserName %></a>
                        <img class="media-object user-avatar" src="Content/Images/default-avatar.png" width="80" height="80" />
                        <span class="blue"><%#: Item.PostDate.ToShortDateString() %><br /><%#: Item.PostDate.ToShortTimeString() %></span>
                    </div>
                    <div class="media-body">
                        <div class="media">
                            <div class="bubble-content">
                                <div class="bubble-point"></div>
                                <p>
                                    <asp:TextBox ID="EditCommentField" TextMode="MultiLine" CssClass="new-comment-text" Text="<%#: BindItem.Text %>" runat="server" />
                                </p>
                            </div>
                        </div>
                    </div>
                </div>
            </li>
        </EditItemTemplate>
        <EmptyDataTemplate>
            <div class="alert alert-info">You can be the first to write a comment in the post.</div>
        </EmptyDataTemplate>
         <LayoutTemplate>
             <ul class="comments-list">
                <asp:PlaceHolder ID="itemPlaceholder" runat="server" />
                <asp:DataPager ID="DataPagerComments" ClientIDMode="Static" runat="server" PagedControlID="CommentsList"
                    PageSize="5">
                    <Fields>
                        <asp:NextPreviousPagerField ButtonCssClass="btn" ShowFirstPageButton="True" ShowNextPageButton="False" />
                        <asp:NumericPagerField />
                        <asp:NextPreviousPagerField ButtonCssClass="btn" ShowLastPageButton="True" ShowPreviousPageButton="False" />
                    </Fields>
                </asp:DataPager>
            </ul>
         </LayoutTemplate>
    </asp:ListView>

    <asp:LoginView ID="LoginAlert" runat="server" ViewStateMode="Disabled">
        <AnonymousTemplate>
            <div class="alert">To comment please log in!</div>
        </AnonymousTemplate>
    </asp:LoginView>

    <asp:PlaceHolder ID="NewComment" runat="server">
        <asp:ValidationSummary ID="NewCommentValidationSummary" ShowModelStateErrors="true" CssClass="alert alert-error" runat="server" />
        <ul class="comments-list">
            <li id="new-comment">
                <div class="media">
                    <div class="pull-left text-center">
                        <a class="btn btn-mini" href="Posts.aspx?user=<%: User.Identity.Name %>"><i class="icon-user"></i> <%: User.Identity.Name %></a>
                        <img class="media-object user-avatar" src="Content/Images/default-avatar.png" width="80" height="80" />
                    </div>
                    <div class="media-body">
                        <div class="media">
                            <div class="bubble-content">
                                <div class="bubble-point"></div>
                                <p><asp:TextBox ID="NewCommentText" CssClass="new-comment-text" TextMode="MultiLine" runat="server"></asp:TextBox></p>
                            </div>
                        </div>
                        <asp:Button ID="CommentBtn" Text="Comment" CssClass="btn" OnClick="CommentBtn_Click" runat="server" />
                    </div>
                </div>    
            </li>
        </ul>
    </asp:PlaceHolder>

</asp:Content>
